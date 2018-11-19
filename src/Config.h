/**
 * Identicon Config
 *
 */
#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>

class Config {
  public:
    Config(char **argv);

    // Setters
    Config* setInput(std::string i);
    Config* setOutput(std::string o);
    Config* setDir(std::string d);
    Config* setWidth(int w);
    Config* setHeight(int h);
    Config* setPadding(int p);

    // Getters
    std::string getInput();
    std::string getOutput();
    std::string getDir();
    int         getWidth();
    int         getHeight();
    int         getPadding();

    // toString
    std::string toString();

  private:
    std::string output;
    std::string dir;
    int width;
    int height;
    std::string input;
    int padding;
};


#endif
