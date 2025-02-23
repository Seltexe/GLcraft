#include <iostream>
#include "GameEngine.hpp"

int main() 
{
    Ge::SWindowInfo window_create_info{};
    window_create_info.w_lenght = 1280;
    window_create_info.w_height = 720;
    window_create_info.w_title = "GLCraft";

    Ge::SRendererCreateInfo renderer_create_info{};
    renderer_create_info.e_renderer_type = Ge::ERendererType::OpenGL33;
    renderer_create_info.p_window_info = &window_create_info;

    Ge::SRenderingEngineCreateInfo rendering_engine_create_info{};
    rendering_engine_create_info.e_rendering_engine_type = Ge::ERenderingEngineType::Rasterization;
    rendering_engine_create_info.p_renderer_create_info = &renderer_create_info;

    Ge::SGameEngineCreateInfo game_engine_create_info{};
    game_engine_create_info.p_rendering_engine_create_info = &rendering_engine_create_info;

    Ge::GameEngine game_engine;

    try
    {
        game_engine.Initialize(game_engine_create_info);
        game_engine.Run();
    }
    catch (std::runtime_error& error)
    {
        std::cerr << "Exception: " << error.what() << std::endl;
    }
    catch (std::bad_alloc& error)
    {
        std::cerr << "Exception: " << error.what() << std::endl;
    }


    return 0;
}