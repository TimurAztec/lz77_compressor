#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/string.hpp>

#ifndef LZ77_1CLION_LOADING_H
#define LZ77_1CLION_LOADING_H

using namespace ftxui;

class Loader {
private:
    Screen screen = Screen::Create(Dimension::Fixed(32), Dimension::Fixed(1));
    Element loading = hbox();
public:
    void load(size_t percent, size_t spinner_number) {
        int dpercent = static_cast<float>(percent);

        loading = hbox({
                                    text(ftxui::to_wstring(dpercent)),
                                    separator(),
                                    gauge(percent * 0.01) | color(Color::Blue),
                                    separator(),
                                    spinner(2, spinner_number)
                            });
        Render(screen, loading);
        std::cout << screen.ToString() << std::endl;
        system("cls");
    }

    void load(size_t percent, size_t spinner_number, std::string stext) {
        int dpercent = static_cast<float>(percent);

        loading = hbox({
                               text(ftxui::to_wstring(dpercent)),
                               separator(),
                               gauge(percent * 0.01) | color(Color::Blue),
                               separator(),
                               spinner(2, spinner_number)
                       });
        Render(screen, loading);
        if (percent < 99) {
            std::cout << stext + ": " + screen.ToString() << "\r";
        } else {
            std::cout << stext << " is done!                                                                       \r";
        }
    }
};

#endif
