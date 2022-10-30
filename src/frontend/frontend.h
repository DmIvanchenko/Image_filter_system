/*
 * frontend.h
 *
 *  Created on: 12 трав. 2022 р.
 *      Author: ImageIt
 */

#ifndef FRONTEND_FRONTEND_H_
#define FRONTEND_FRONTEND_H_

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
#include "../backend/CropFilter.h"
#include "../backend/RotateFilter.h"
#include "../backend/Node.h"

// NOTE: namespace is intended for enumeration to work
namespace Item {

enum Type {
    GRAYSCALE = 0,
    EXPOSURE = 1,
    GAUSSIAN_BLUR = 2,
    CROP = 3,
    ROTATE = 4
};
const int LEN = 5;

std::shared_ptr<backend::FilterBase> make_filter(Type t);

}

class MainWindow: public Gtk::ApplicationWindow {
public:
    static const int NPARAMS = 4;
    Gtk::Button Item_button[Item::LEN];
    Gtk::Label *Name_filter_label,
            *Name_param_label[NPARAMS];
    Gtk::ImageMenuItem *Open_item, *Save_item,
            *Save_as_item, Add_item[Item::LEN],
            Remove_item[Item::LEN];
    Gtk::MenuItem *Edit_menu;
    Gtk::HScale *Hscale[NPARAMS];
    Gtk::MenuItem *Add_filter_item, *Remove_filter_item;
    Gtk::Image *Main_Image_image;
    Gtk::VBox *Buttons_panel;
    short number_applied_filters = 0;
    std::optional<
            std::pair<Item::Type,
                    std::shared_ptr<backend::FilterBase>>> selected =
            std::nullopt;
    backend::Pipeline pipeline;

    // sometimes it is needed just to access static fields
    const std::shared_ptr<backend::FilterBase> FILTER[Item::LEN] {
            std::make_shared<backend::GrayscaleFilter>(),
            std::make_shared<backend::ExposureFilter>(),
            std::make_shared<backend::GaussianBlurFilter>(),
            std::make_shared<backend::CropFilter>(),
            std::make_shared<backend::RotateFilter>() };

    void hide_panel();
    void check_add();
    void check_remove(Item::Type);
    void add_item(Item::Type);
    void remove_item(Item::Type);
    void select_item(Item::Type);
    void change_scale(int);
    void Open();
    void Save();
    void SaveAs();
    MainWindow(BaseObjectType *obj,
            Glib::RefPtr<Gtk::Builder> const &builder);
    virtual ~MainWindow() = default;

private:
    Glib::RefPtr<Gtk::Builder> builder;
};

int frontend_main(int argc, char *argv[]);

#endif /* FRONTEND_FRONTEND_H_ */
