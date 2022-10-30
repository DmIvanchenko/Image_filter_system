#include "frontend.h"
#include <memory>
#include <gtkmm.h>
#include <iostream>
#include <array>
#include <memory>
#include <optional>
#include "../backend/Pipeline.h"
#include "../backend/ImportFilter.h"
#include "../backend/ExposureFilter.h"
#include "../backend/GrayscaleFilter.h"
#include "../backend/GaussianBlurFilter.h"
#include "../backend/Node.h"
#include "../debug/debug.h"

#define UI_FILE "mainForm.glade"
#define COUNT_FILTERS

using namespace Gtk;
using namespace Glib;
using namespace std;

std::shared_ptr<backend::FilterBase> Item::make_filter(
        Item::Type t) {
    switch (t) {
    case GRAYSCALE:
        return std::make_shared<backend::GrayscaleFilter>();
    case EXPOSURE:
        return std::make_shared<backend::ExposureFilter>();
    case GAUSSIAN_BLUR:
        return std::make_shared<backend::GaussianBlurFilter>();
    case CROP:
        return std::make_shared<backend::CropFilter>();
    case ROTATE:
        return std::make_shared<backend::RotateFilter>();
    }
    throw; // ArgumentException
}

void MainWindow::hide_panel() {
    selected = nullopt;
    Name_filter_label->set_visible(false);
    for (int i = 0; i < NPARAMS; i++) {
        Name_param_label[i]->set_visible(false);
        Hscale[i]->set_visible(false);
    }
}

void MainWindow::check_add() {
    number_applied_filters++;
    Add_filter_item->set_visible(
            number_applied_filters < Item::LEN);
    if (number_applied_filters == 1)
        Remove_filter_item->show();
}

void MainWindow::check_remove(Item::Type item) {
    number_applied_filters--;
    if (number_applied_filters <= 0) {
        number_applied_filters = 0;
        Remove_filter_item->hide();
        hide_panel();
    }
    if (selected && item == (*selected).first) {
        hide_panel();
    }
    if (number_applied_filters == Item::LEN - 1) {
        Add_filter_item->show();
    }
}

void MainWindow::add_item(Item::Type item) {
    Item_button[item].show();
    Add_item[item].hide();
    Remove_item[item].show();

    check_add();

    shared_ptr<backend::FilterBase> filter =
            Item::make_filter(item);
    shared_ptr<backend::Node> node = make_shared<
            backend::Node>(backend::Node { filter });
    pipeline.append_node(node);
    cerr << "Added filter to pipeline" << endl;
}

void MainWindow::remove_item(Item::Type item) {
    Item_button[item].hide();
    Add_item[item].show();
    Remove_item[item].hide();

    check_remove(item);

    optional<int> idx_opt = pipeline.get_node_index_by_name(
            FILTER[item]->get_name());

    if (idx_opt) {
        pipeline.remove_node_at(*idx_opt);
        cerr << "Removed filter from pipeline" << endl;
    } else {
        cerr << "W: Filter not found -- skipping" << endl;
    }
}

void MainWindow::select_item(Item::Type item) {
    const char *filter_name = FILTER[item]->get_name();
    hide_panel();
    Name_filter_label->set_text(filter_name);
    Name_filter_label->show();
    auto filter = pipeline.get_filter_by_name(filter_name);
    if (!filter) {
        cerr << "E: Filter was not found in the pipeline"
                << " -- stopping" << endl;
        throw;
    }
    selected = std::make_pair(item, *filter);
    int i = 0;
    for (auto param : (*filter)->get_param_list()) {
        backend::ParamInfo &info = param.first;
        const char *param_name = info.name.c_str();

        Name_param_label[i]->set_text(param_name);
        Name_param_label[i]->show();
        Hscale[i]->set_visible(
                info.type
                        == backend::ParamType::DOUBLE_RANGE
                        || info.type
                                == backend::ParamType::INT_RANGE);
        switch (info.type) {
        case backend::ParamType::DOUBLE_RANGE:
            Hscale[i]->set_range(info.range_from,
                    info.range_to);
            Hscale[i]->set_digits(2);
            Hscale[i]->set_value(
                    std::get<double>(param.second.value));
            break;
        case backend::ParamType::INT_RANGE:
            Hscale[i]->set_range(info.irange_from,
                    info.irange_to);
            Hscale[i]->set_digits(0);
            Hscale[i]->set_value(
                    std::get<int>(param.second.value));
            break;
        default:
            cerr << "W: The parameter type has no GUI"
                    << " implemented -- skipping" << endl;
            break;
        }
        i++;
    }
}

void MainWindow::change_scale(int idx) {
    if (!selected) {
        cerr << "E: changing slider value without"
                << " a selected filter -- quitting" << endl;
        throw;
    }
    backend::ParamType type =
            (*selected).second->get_param_value(idx).type;
    if (type == backend::ParamType::DOUBLE_RANGE) {
        double val = Hscale[idx]->get_value();
        backend::ParamValue pval =
                backend::ParamValue::double_range(val);
        (*selected).second->set_param_value(idx, pval);
    } else if (type == backend::ParamType::INT_RANGE) {
        int val = (int) Hscale[idx]->get_value();
        backend::ParamValue pval =
                backend::ParamValue::int_range(val);
        (*selected).second->set_param_value(idx, pval);
    } else {
        cerr << "E: changing slider value of a "
                << "non-numeric parameter -- quitting"
                << endl;
        throw;
    }
    cout << "Change scale " << idx << endl;
}

void MainWindow::Open() {
    cout << "Open" << endl;

    GtkFileChooserNative *native;
    GtkFileChooserAction action =
            GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    native = gtk_file_chooser_native_new("Open File",
    NULL, action, "_Open", "_Cancel");

    res = gtk_native_dialog_run(GTK_NATIVE_DIALOG(native));

    if (res == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(native);
        filename = gtk_file_chooser_get_filename(chooser);
        pipeline = backend::Pipeline();
        shared_ptr<backend::FilterBase> filter =
                make_shared<backend::ImportFilter>();
        // add a path as a filter parameter
        filter.get()->set_param_value(0,
                backend::ParamValue::file_path(filename));
        shared_ptr<backend::Node> node = make_shared<
                backend::Node>(backend::Node { filter });
        pipeline.append_node(node);
        Edit_menu->show();
        Save_item->show();
        Save_as_item->show();
        hide_panel();
        for (int i = 0; i < Item::LEN; i++) {
            Item_button[i].hide();
            Add_item[i].show();
            check_remove((Item::Type) i);
        }
        Main_Image_image->set(filename);
        cerr << "Pipeline was cleared; added ImportFilter"
                << endl;
        g_free(filename);
    }

    g_object_unref(native);

}

void MainWindow::Save() {
    cout << "Save" << endl;
    const char *OUTPATH = "out.png";
    pipeline.evaluate();
    pipeline.export_result(OUTPATH);
    cerr << "Saved to " << OUTPATH << endl;
    debug::preview_image(OUTPATH);
}

void MainWindow::SaveAs() {
    cout << "SaveAs" << endl;

    GtkFileChooserNative *native;
    GtkFileChooserAction action =
            GTK_FILE_CHOOSER_ACTION_SAVE;
    gint res;

    native = gtk_file_chooser_native_new("Save File As",
    NULL, action, "_Save", "_Cancel");

    res = gtk_native_dialog_run(GTK_NATIVE_DIALOG(native));

    if (res == GTK_RESPONSE_ACCEPT) {
        char *foldername;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(native);
        foldername = gtk_file_chooser_get_filename(chooser);
        pipeline.evaluate();
        pipeline.export_result(foldername);
    }

    g_object_unref(native);
}

MainWindow::MainWindow(BaseObjectType *obj,
        RefPtr<Builder> const &builder) :
        ApplicationWindow(obj), builder { builder } {
    builder->get_widget("hscale_1", Hscale[0]);
    builder->get_widget("hscale_2", Hscale[1]);
    builder->get_widget("hscale_3", Hscale[2]);
    builder->get_widget("hscale_4", Hscale[3]);
    builder->get_widget("Name_filter", Name_filter_label);
    builder->get_widget("Name_param_1",
            Name_param_label[0]);
    builder->get_widget("Name_param_2",
            Name_param_label[1]);
    builder->get_widget("Name_param_3",
            Name_param_label[2]);
    builder->get_widget("Name_param_4",
            Name_param_label[3]);
    builder->get_widget("Open", Open_item);
    builder->get_widget("Save", Save_item);
    builder->get_widget("Save_as", Save_as_item);
    builder->get_widget("Add_filter", Add_filter_item);
    builder->get_widget("Buttons_panel", Buttons_panel);
    builder->get_widget("Remove_filter",
            Remove_filter_item);
    builder->get_widget("Edit", Edit_menu);
    builder->get_widget("Image", Main_Image_image);
    for (int i = 0; i < Item::LEN; i++) {
        const char *name = FILTER[i]->get_name();
        Add_item[i] = Gtk::ImageMenuItem { name };
        Add_filter_item->get_submenu()->add(Add_item[i]);
        Add_item[i].show();

        Remove_item[i] = Gtk::ImageMenuItem { name };
        Remove_filter_item->get_submenu()->add(
                Remove_item[i]);

        Item_button[i] = Gtk::Button { name };
        Buttons_panel->add(Item_button[i]);
    }

    // set basic values
    Edit_menu->hide();
    Save_item->hide();
    Save_as_item->hide();
    Remove_filter_item->hide();
    hide_panel();

    // Connect signals
    for (int i = 0; i < NPARAMS; i++) {
        Hscale[i]->signal_value_changed().connect(
                sigc::bind([](MainWindow *that, int at) {
                    that->change_scale(at);
                }, this, i));
    }
    Open_item->signal_activate().connect(
            sigc::mem_fun(*this, &MainWindow::Open));
    Save_item->signal_activate().connect(
            sigc::mem_fun(*this, &MainWindow::Save));
    Save_as_item->signal_activate().connect(
            sigc::mem_fun(*this, &MainWindow::SaveAs));

    for (int i = 0; i < Item::LEN; i++) {
        Item_button[i].signal_clicked().connect(
                sigc::bind(
                        [](MainWindow *that,
                                Item::Type at) {
                            that->select_item(at);
                        }, this, (Item::Type) i));
        Add_item[i].signal_activate().connect(
                sigc::bind([](MainWindow *a, int at) {
                    a->add_item((Item::Type) at);
                }, this, i));
        Remove_item[i].signal_activate().connect(
                sigc::bind([](MainWindow *a, int at) {
                    a->remove_item((Item::Type) at);
                }, this, i));
    }
}

int frontend_main(int argc, char *argv[]) {
    auto app = Application::create(argc, argv,
            "de.engelmarkus.example");
    auto builder = Builder::create_from_file(
            "res/mainForm.glade");

    MainWindow *wnd = nullptr;

    builder->get_widget_derived("topWindow", wnd);

    GtkCssProvider *cssProvider = gtk_css_provider_new();
    if (gtk_css_provider_load_from_path(cssProvider,
            "res/style.css", NULL)) {
        gtk_style_context_add_provider_for_screen(
                gdk_screen_get_default(),
                GTK_STYLE_PROVIDER(cssProvider),
                GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    }

    auto r = app->run(*wnd);

    delete wnd;

    return r;
}
