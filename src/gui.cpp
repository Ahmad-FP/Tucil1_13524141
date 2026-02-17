#include <gtkmm.h>
#include <fstream>
#include <sstream>
#include "normal.cpp"
#include "Optimized.cpp"

using namespace std;
using namespace Gtk;


class window : public Window {
Label slide_label;
Box box, mid,slide_box;
ScrolledWindow in_scroll, out_scroll;
TextView in_view, out_view;
Button load_btn, process_btn, optimized_btn;
Scale slide;
int k=1;

public:
    window() {
        set_title("Tucil1");
        set_default_size(600,800);

        box.set_orientation(Orientation::VERTICAL);

        load_btn.set_label("Load txt");
        process_btn.set_label("Process");
        optimized_btn.set_label("Optimized Process");

        load_btn.signal_clicked().connect([this]() { load_file(); });
        process_btn.signal_clicked().connect([this]() { process(); });
        optimized_btn.signal_clicked().connect([this](){processOptimized();});
        

        mid.append(load_btn);
        mid.append(process_btn);
        mid.append(optimized_btn);
        mid.set_halign(Align::CENTER);

        auto adj = Adjustment::create(1,1,1000000,10);
        slide.set_adjustment(adj);
        slide.set_draw_value(true);
        slide_label.set_text("Live Update Frequency (Higher is lower)");
        slide.signal_value_changed().connect([this](){slidechange();});
        
        slide_box.set_orientation(Orientation::VERTICAL);
        slide_box.append(slide_label);
        slide_box.append(slide);


        in_scroll.set_child(in_view);
        in_scroll.set_vexpand(true);
        out_scroll.set_child(out_view);
        out_scroll.set_vexpand(true);
        
        box.append(in_scroll);
        box.append(mid);
        box.append(slide_box);
        box.append(out_scroll);

        set_child(box);
    }

private:
   void load_file() {
        auto dialog = Gtk::FileDialog::create();
        dialog->set_title("Select a TXT File");
        
        dialog->open(*this, [this, dialog](auto res) {
            auto file = dialog->open_finish(res);
            if (file) {
                std::ifstream i(file->get_path());
                std::stringstream ss;
                ss << i.rdbuf();
                in_view.get_buffer()->set_text(ss.str());
            }
            
        });
    }   

    void processOptimized() {
        string text = in_view.get_buffer()->get_text();

        ostringstream out;
        streambuf* buf = cout.rdbuf(out.rdbuf());
        solveO(text,k);
        cout.rdbuf(buf);

        out_view.get_buffer()->set_text(out.str());
    }

    void process() {
        string text = in_view.get_buffer()->get_text();

        ostringstream out;
        streambuf* buf = cout.rdbuf(out.rdbuf());
        solveN(text,k);
        cout.rdbuf(buf);
        out_view.get_buffer()->set_text(out.str());
    }

    void slidechange(){
        k = slide.get_value();
    }
    
};

int main(int argc, char** argv) {
    auto app = Application::create();
    return app->make_window_and_run<window>(argc, argv);
}