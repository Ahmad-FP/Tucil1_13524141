#include <gtkmm.h>
#include <fstream>
#include <sstream>
#include <thread>
#include "normal.cpp"
#include "Optimized.cpp"

using namespace std;
using namespace Gtk;

ostringstream sout;


class window : public Window {
Box box, mid,kslidebox,tslidebox;
ScrolledWindow in_scroll, out_scroll;
TextView in_view, out_view;
Button load_btn, process_btn, optimized_btn,save_btn;
Label kslidelabel,tslidelabel;
Scale kslide, tslide;
int k=1;
int t = 100;
thread* thr;
sigc::connection timer;

public:
    window() {

        set_title("Tucil1");
        set_default_size(600,800);

        box.set_orientation(Orientation::VERTICAL);

        load_btn.set_label("Load txt");
        process_btn.set_label("Process");
        optimized_btn.set_label("Optimized Process");
        save_btn.set_label("Save Output");

        load_btn.signal_clicked().connect([this]() { load_file(); });
        process_btn.signal_clicked().connect([this]() { process(); });
        optimized_btn.signal_clicked().connect([this](){processOptimized();});
        save_btn.signal_clicked().connect([this](){save();});

        mid.append(load_btn);
        mid.append(process_btn);
        mid.append(optimized_btn);
        mid.append(save_btn);
        mid.set_halign(Align::CENTER);

        auto adj = Adjustment::create(1,1,1000000,1000,1000);
        kslide.set_adjustment(adj);
        kslide.set_draw_value(true);
        kslidelabel.set_text("Output Interval in Cases (Higher is lower)");
        kslide.signal_value_changed().connect([this](){kslidechange();});

        kslidebox.set_orientation(Orientation::VERTICAL);
        kslidebox.append(kslidelabel);
        kslidebox.append(kslide);

        auto tadj = Adjustment::create(1,100,3000,100,1000);
        tslide.set_adjustment(tadj);
        tslide.set_draw_value(true);
        tslidelabel.set_text("Output Interval in Milliseconds");
        tslide.signal_value_changed().connect([this](){tslidechange();});

        tslidebox.set_orientation(Orientation::VERTICAL);
        tslidebox.append(tslidelabel);
        tslidebox.append(tslide);

        in_scroll.set_child(in_view);
        in_scroll.set_vexpand(true);
        out_scroll.set_child(out_view);
        out_scroll.set_vexpand(true);
        
        box.append(in_scroll);
        box.append(mid);
        box.append(kslidebox);
        box.append(tslidebox);
        box.append(out_scroll);

        set_child(box);
    }

private:

    void save(){

        auto dialog = FileDialog::create();
        dialog->set_title("Save Output as TXT");
        dialog->set_initial_name("Output.txt");

        dialog->save(*this, [this, dialog](auto res){
            auto file= dialog->save_finish(res);
            if(file){
                ofstream o(file->get_path());
                o << out_view.get_buffer()->get_text();
                o.close();
            }

        });

    }
   void load_file() {
        auto dialog = Gtk::FileDialog::create();
        dialog->set_title("Select a TXT File");
        
        dialog->open(*this, [this, dialog](auto res) {
            auto file = dialog->open_finish(res);
            if (file) {
                ifstream i(file->get_path());
                stringstream ss;
                ss << i.rdbuf();
                in_view.get_buffer()->set_text(ss.str());
            }
            
        });
    }   

    void processOptimized() {
        if(thr && thr->joinable()) thr->join();
        if(timer.connected()) timer.disconnect();

        sout.str("");
        string text = in_view.get_buffer()->get_text();
        int curk = k;
        thr = new thread([text, curk]() {
            streambuf* ori = cout.rdbuf();
            cout.rdbuf(sout.rdbuf());
            solveO(text, curk);
            cout.rdbuf(ori);
        });

        timer = Glib::signal_timeout().connect([this]() {
            out_view.get_buffer()->set_text(sout.str()); 
            if(thr && !thr->joinable()) {
                thr->join();
                return false;
            }
            return true;
        }, t);
    }

    void process() {
        if(thr && thr->joinable()) thr->join();
        if(timer.connected()) timer.disconnect();

        sout.str("");
        string text = in_view.get_buffer()->get_text();
        int curk = k;
        thr = new thread([text, curk]() {
            streambuf* ori = cout.rdbuf();
            cout.rdbuf(sout.rdbuf());
            solveN(text, curk);
            cout.rdbuf(ori);
        });

        timer = Glib::signal_timeout().connect([this]() {
            out_view.get_buffer()->set_text(sout.str());
            if(thr && !thr->joinable()) {
                thr->join();
                return false;
            }
            return true;
        }, t);
    }

    void kslidechange(){
        k = kslide.get_value();
    }
    void tslidechange(){
        t = tslide.get_value();
    }
};

int main(int argc, char** argv) {
    auto app = Application::create();
    return app->make_window_and_run<window>(argc, argv);
}