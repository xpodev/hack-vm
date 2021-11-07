// HackVM.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>

#include <SDL.h>

#include "App.h"
#include "HackComputer.h"

constexpr size_t const HackComputerMemorySize = 24576;
constexpr size_t const HackUIWidth = 512, HackUIHeight = 256;
constexpr size_t const HackUIBaseAddress = 16384;


class HackUI : public App {
public:
    HackUI(HackComputer& pc, Hack__size_t* program)
        : App(HackUIWidth, HackUIHeight)
        , m_screen{ nullptr }
        , m_screenData{ new Uint32[HackUIWidth * HackUIHeight] }
        , m_pcMemory{ pc.memory() }
        , m_pc{ pc }
        , m_program{ program }
    {}

protected:
    bool OnInit() override {
        if (!App::OnInit()) return false;
        if ((m_screen = SDL_CreateTexture(
            GetRenderer(), 
            SDL_PIXELFORMAT_RGBA32, 
            SDL_TEXTUREACCESS_STREAMING, 
            HackUIWidth, HackUIHeight)) == nullptr) return false;
        return true;
    }

    void OnLoop() override {
        m_pc.run(m_program, m_programCounter);
        // todo: only redraw when screen memory changes
        for (int i = 0; i < HackUIWidth * HackUIHeight;) {
            Hack__size_t word = m_pcMemory[HackUIBaseAddress + i / (sizeof(Hack__size_t) * 8)];
            for (int bit = sizeof(Hack__size_t) - 1; bit >= 0; --bit, ++i) {
                m_screenData[i] = word & (1 << bit) ? 0 : -1;
            }
        }
        if (SDL_UpdateTexture(m_screen, nullptr, m_screenData, HackUIWidth * sizeof(Uint32)) < 0)
            SDL_Log("%s", SDL_GetError());
        SDL_RenderCopy(GetRenderer(), m_screen, nullptr, nullptr);
        ReDraw();
    }

private:
    SDL_Texture* m_screen;
    Uint32* m_screenData;
    Hack__size_t* m_pcMemory;
    Hack__size_t* m_program;
    HackComputer& m_pc;
    Hack__size_t m_programCounter = 0;
};


#ifdef main
#undef main
#endif


int main(int argc, char** argv)
{
    char* path;
    if (argc > 1) {
        path = argv[1];
    }
    else return 1;

    std::ifstream binary;
    binary.open(path, std::ios::in | std::ios::binary | std::ios::ate);
    if (!binary.is_open()) {
        std::cout << "Could not open file \"" << path << "\"" << std::endl;
        return 1;
    }
    std::streamsize fileSize = binary.tellg();
    char* buffer = new char[fileSize];
    binary.seekg(0, std::ios::beg);
    binary.read(buffer, fileSize);

    HackComputer pc = HackComputer(HackComputerMemorySize);
    pc.memory()[0] = 30;
    pc.memory()[1] = 30;
    HackUI ui{ pc, reinterpret_cast<Hack__size_t*>(buffer) };
    return ui.OnExecute();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
