#include "imgui-SFML.h"
#include "imgui.h"

#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>

#include <cmath> // abs
#include <cstddef> // offsetof, NULL
#include <cassert>
#include <SFML/Window/Touch.hpp>

#ifdef ANDROID
#ifdef USE_JNI

#include <jni.h>
#include <android/native_activity.h>
#include <SFML/System/NativeActivity.hpp>

static bool s_wantTextInput = false;

int openKeyboardIME()
{
    ANativeActivity *activity = sf::getNativeActivity();
    JavaVM* vm = activity->vm;
    JNIEnv* env = activity->env;
    JavaVMAttachArgs attachargs;
    attachargs.version = JNI_VERSION_1_6;
    attachargs.name = "NativeThread";
    attachargs.group = NULL;
    jint res = vm->AttachCurrentThread(&env, &attachargs);
    if (res == JNI_ERR)
        return EXIT_FAILURE;

    jclass natact = env->FindClass("android/app/NativeActivity");
    jclass context = env->FindClass("android/content/Context");

    jfieldID fid = env->GetStaticFieldID(context, "INPUT_METHOD_SERVICE", "Ljava/lang/String;");
    jobject svcstr = env->GetStaticObjectField(context, fid);


    jmethodID getss = env->GetMethodID(natact, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
    jobject imm_obj = env->CallObjectMethod(activity->clazz, getss, svcstr);

    jclass imm_cls = env->GetObjectClass(imm_obj);
    jmethodID toggleSoftInput = env->GetMethodID(imm_cls, "toggleSoftInput", "(II)V");

    env->CallVoidMethod(imm_obj, toggleSoftInput, 2, 0);

    env->DeleteLocalRef(imm_obj);
    env->DeleteLocalRef(imm_cls);
    env->DeleteLocalRef(svcstr);
    env->DeleteLocalRef(context);
    env->DeleteLocalRef(natact);

    vm->DetachCurrentThread();

    return EXIT_SUCCESS;

}

int closeKeyboardIME()
{
    ANativeActivity *activity = sf::getNativeActivity();
    JavaVM* vm = activity->vm;
    JNIEnv* env = activity->env;
    JavaVMAttachArgs attachargs;
    attachargs.version = JNI_VERSION_1_6;
    attachargs.name = "NativeThread";
    attachargs.group = NULL;
    jint res = vm->AttachCurrentThread(&env, &attachargs);
    if (res == JNI_ERR)
        return EXIT_FAILURE;

    jclass natact = env->FindClass("android/app/NativeActivity");
    jclass context = env->FindClass("android/content/Context");

    jfieldID fid = env->GetStaticFieldID(context, "INPUT_METHOD_SERVICE", "Ljava/lang/String;");
    jobject svcstr = env->GetStaticObjectField(context, fid);


    jmethodID getss = env->GetMethodID(natact, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
    jobject imm_obj = env->CallObjectMethod(activity->clazz, getss, svcstr);

    jclass imm_cls = env->GetObjectClass(imm_obj);
    jmethodID toggleSoftInput = env->GetMethodID(imm_cls, "toggleSoftInput", "(II)V");

    env->CallVoidMethod(imm_obj, toggleSoftInput, 1, 0);

    env->DeleteLocalRef(imm_obj);
    env->DeleteLocalRef(imm_cls);
    env->DeleteLocalRef(svcstr);
    env->DeleteLocalRef(context);
    env->DeleteLocalRef(natact);

    vm->DetachCurrentThread();

    return EXIT_SUCCESS;

}

#endif
#endif

// Supress warnings caused by converting from uint to void* in pCmd->TextureID
#ifdef __clang__
#pragma clang diagnostic ignored "-Wint-to-void-pointer-cast" // warning : cast to 'void *' from smaller integer type 'int'
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"      // warning: cast to pointer from integer of different size
#endif

static bool s_windowHasFocus = true;
static bool s_mousePressed[3] = { false, false, false };
static bool s_touchDown[3] = { false, false, false };
static bool s_mouseMoved = false;
static sf::Vector2i s_touchPos;
static sf::Texture* s_fontTexture = NULL; // owning pointer to internal font atlas which is used if user doesn't set custom sf::Texture.
namespace
{

ImVec2 getTopLeftAbsolute(const sf::FloatRect& rect);
ImVec2 getDownRightAbsolute(const sf::FloatRect& rect);

void RenderDrawLists(ImDrawData* draw_data); // rendering callback function prototype

// Implementation of ImageButton overload
bool imageButtonImpl(const sf::Texture& texture, const sf::FloatRect& textureRect, const sf::Vector2f& size, const int framePadding,
                     const sf::Color& bgColor, const sf::Color& tintColor);

} // anonymous namespace for helper / "private" functions

namespace ImGui
{
namespace SFML
{

void Init(sf::RenderTarget& target, bool loadDefaultFont)
{
    ImGuiIO& io = ImGui::GetIO();

    // init keyboard mapping
    io.KeyMap[ImGuiKey_Tab] = sf::Keyboard::Tab;
    io.KeyMap[ImGuiKey_LeftArrow] = sf::Keyboard::Left;
    io.KeyMap[ImGuiKey_RightArrow] = sf::Keyboard::Right;
    io.KeyMap[ImGuiKey_UpArrow] = sf::Keyboard::Up;
    io.KeyMap[ImGuiKey_DownArrow] = sf::Keyboard::Down;
    io.KeyMap[ImGuiKey_PageUp] = sf::Keyboard::PageUp;
    io.KeyMap[ImGuiKey_PageDown] = sf::Keyboard::PageDown;
    io.KeyMap[ImGuiKey_Home] = sf::Keyboard::Home;
    io.KeyMap[ImGuiKey_End] = sf::Keyboard::End;
#ifdef ANDROID
    io.KeyMap[ImGuiKey_Backspace] = sf::Keyboard::Delete;
#else
    io.KeyMap[ImGuiKey_Delete] = sf::Keyboard::Delete;
    io.KeyMap[ImGuiKey_Backspace] = sf::Keyboard::BackSpace;
#endif
    io.KeyMap[ImGuiKey_Enter] = sf::Keyboard::Return;
    io.KeyMap[ImGuiKey_Escape] = sf::Keyboard::Escape;
    io.KeyMap[ImGuiKey_A] = sf::Keyboard::A;
    io.KeyMap[ImGuiKey_C] = sf::Keyboard::C;
    io.KeyMap[ImGuiKey_V] = sf::Keyboard::V;
    io.KeyMap[ImGuiKey_X] = sf::Keyboard::X;
    io.KeyMap[ImGuiKey_Y] = sf::Keyboard::Y;
    io.KeyMap[ImGuiKey_Z] = sf::Keyboard::Z;

    // init rendering
    io.DisplaySize = static_cast<sf::Vector2f>(target.getSize());
    io.RenderDrawListsFn = RenderDrawLists; // set render callback

    if (s_fontTexture) { // delete previously created texture
        delete s_fontTexture;
    }
    s_fontTexture = new sf::Texture;

    if (loadDefaultFont) {
        // this will load default font automatically
        // No need to call AddDefaultFont
        UpdateFontTexture();
    }
}

void ProcessEvent(const sf::Event& event)
{
    ImGuiIO& io = ImGui::GetIO();
    if (s_windowHasFocus) {
        switch (event.type)
        {
            case sf::Event::MouseMoved:
                s_mouseMoved = true;
                break;
            case sf::Event::MouseButtonPressed: // fall-through
            case sf::Event::MouseButtonReleased:
                {
                    int button = event.mouseButton.button;
                    if (event.type == sf::Event::MouseButtonPressed &&
                        button >= 0 && button < 3) {
                        s_mousePressed[event.mouseButton.button] = true;
                    }
                }
                break;
            case sf::Event::TouchBegan: // fall-through
            case sf::Event::TouchEnded:
                {
                    s_mouseMoved = false;
                    int button = event.touch.finger;
                    if (event.type == sf::Event::TouchBegan &&
                        button >= 0 && button < 3) {
                        s_touchDown[event.touch.finger] = true;
                    }
                }
                break;
            case sf::Event::MouseWheelMoved:
                io.MouseWheel += static_cast<float>(event.mouseWheel.delta);
                break;
            case sf::Event::KeyPressed: // fall-through
            case sf::Event::KeyReleased:
                io.KeysDown[event.key.code] = (event.type == sf::Event::KeyPressed);
                io.KeyCtrl = event.key.control;
                io.KeyShift = event.key.shift;
                io.KeyAlt = event.key.alt;
                break;
            case sf::Event::TextEntered:
                if (event.text.unicode > 0 && event.text.unicode < 0x10000) {
                    io.AddInputCharacter(static_cast<ImWchar>(event.text.unicode));
                }
                break;
            default:
                break;
        }
    }

    switch (event.type)
    {
        case sf::Event::LostFocus:
            s_windowHasFocus = false;
            break;
        case sf::Event::GainedFocus:
            s_windowHasFocus = true;
            break;
        default:
            break;
    }
}

void Update(sf::RenderWindow& window, sf::Time dt)
{
    Update(window, window, dt);
}

void Update(sf::Window& window, sf::RenderTarget& target, sf::Time dt)
{

    if (!s_mouseMoved)
    {
        if (sf::Touch::isDown(0))
            s_touchPos = sf::Touch::getPosition(0, window);

        Update(s_touchPos, static_cast<sf::Vector2f>(target.getSize()), dt);
    } else {
        Update(sf::Mouse::getPosition(window), static_cast<sf::Vector2f>(target.getSize()), dt);
    }
    window.setMouseCursorVisible(!ImGui::GetIO().MouseDrawCursor); // don't draw mouse cursor if ImGui draws it
}

void Update(const sf::Vector2i& mousePos, const sf::Vector2f& displaySize, sf::Time dt)
{
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = displaySize;
    io.DeltaTime = dt.asSeconds();

    if (s_windowHasFocus) {
        io.MousePos = mousePos;
        for (unsigned int i = 0; i < 3; i++) {
            io.MouseDown[i] =  s_touchDown[i] || sf::Touch::isDown(i) || s_mousePressed[i] || sf::Mouse::isButtonPressed((sf::Mouse::Button)i);
            s_mousePressed[i] = false;
            s_touchDown[i] = false;
        }
    }

#ifdef ANDROID
#ifdef USE_JNI
        if (io.WantTextInput && !s_wantTextInput)
        {
            openKeyboardIME();
            s_wantTextInput = true;
        }
        if (!io.WantTextInput && s_wantTextInput)
        {
            closeKeyboardIME();
            s_wantTextInput = false;
        }
#endif
#endif

    assert(io.Fonts->Fonts.Size > 0); // You forgot to create and set up font atlas (see createFontTexture)
    ImGui::NewFrame();
}

void Render(sf::RenderTarget& target)
{
    target.resetGLStates();
    ImGui::Render();
}

void Shutdown()
{
    ImGui::GetIO().Fonts->TexID = NULL;

    if (s_fontTexture) { // if internal texture was created, we delete it
        delete s_fontTexture;
        s_fontTexture = NULL;
    }

    //ImGui::Shutdown(); // need to specify namespace here, otherwise ImGui::SFML::Shutdown would be called
}

void UpdateFontTexture()
{
    sf::Texture& texture = *s_fontTexture;

    ImGuiIO& io = ImGui::GetIO();
    unsigned char* pixels;
    int width, height;

    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

    texture.create(width, height);
    texture.update(pixels);

    io.Fonts->TexID = (void*)texture.getNativeHandle();

    io.Fonts->ClearInputData();
    io.Fonts->ClearTexData();
}

sf::Texture& GetFontTexture()
{
    return *s_fontTexture;
}

} // end of namespace SFML


/////////////// Image Overloads

void Image(const sf::Texture& texture,
    const sf::Color& tintColor, const sf::Color& borderColor)
{
    Image(texture, static_cast<sf::Vector2f>(texture.getSize()), tintColor, borderColor);
}

void Image(const sf::Texture& texture, const sf::Vector2f& size,
    const sf::Color& tintColor, const sf::Color& borderColor)
{
    ImGui::Image((void*)texture.getNativeHandle(), size, ImVec2(0, 0), ImVec2(1, 1), tintColor, borderColor);
}

void Image(const sf::Texture& texture, const sf::FloatRect& textureRect,
    const sf::Color& tintColor, const sf::Color& borderColor)
{
    Image(texture, sf::Vector2f(std::abs(textureRect.width), std::abs(textureRect.height)), textureRect, tintColor, borderColor);
}

void Image(const sf::Texture& texture, const sf::Vector2f& size, const sf::FloatRect& textureRect,
    const sf::Color& tintColor, const sf::Color& borderColor)
{
    sf::Vector2f textureSize = static_cast<sf::Vector2f>(texture.getSize());
    ImVec2 uv0(textureRect.left / textureSize.x, textureRect.top / textureSize.y);
    ImVec2 uv1((textureRect.left + textureRect.width) / textureSize.x,
        (textureRect.top + textureRect.height) / textureSize.y);
    ImGui::Image((void*)texture.getNativeHandle(), size, uv0, uv1, tintColor, borderColor);
}

void Image(const sf::Sprite& sprite,
    const sf::Color& tintColor, const sf::Color& borderColor)
{
    sf::FloatRect bounds = sprite.getGlobalBounds();
    Image(sprite, sf::Vector2f(bounds.width, bounds.height), tintColor, borderColor);
}

void Image(const sf::Sprite& sprite, const sf::Vector2f& size,
    const sf::Color& tintColor, const sf::Color& borderColor)
{
    const sf::Texture* texturePtr = sprite.getTexture();
    // sprite without texture cannot be drawn
    if (!texturePtr) { return; }

    Image(*texturePtr, size, tintColor, borderColor);
}

/////////////// Image Button Overloads

bool ImageButton(const sf::Texture& texture,
    const int framePadding, const sf::Color& bgColor, const sf::Color& tintColor)
{
    return ImageButton(texture, static_cast<sf::Vector2f>(texture.getSize()), framePadding, bgColor, tintColor);
}

bool ImageButton(const sf::Texture& texture, const sf::Vector2f& size,
    const int framePadding, const sf::Color& bgColor, const sf::Color& tintColor)
{
    sf::Vector2f textureSize = static_cast<sf::Vector2f>(texture.getSize());
    return ::imageButtonImpl(texture, sf::FloatRect(0.f, 0.f, textureSize.x, textureSize.y), size, framePadding, bgColor, tintColor);
}

bool ImageButton(const sf::Sprite& sprite,
    const int framePadding, const sf::Color& bgColor, const sf::Color& tintColor)
{
    sf::FloatRect spriteSize = sprite.getGlobalBounds();
    return ImageButton(sprite, sf::Vector2f(spriteSize.width, spriteSize.height), framePadding, bgColor, tintColor);
}

bool ImageButton(const sf::Sprite& sprite, const sf::Vector2f& size,
    const int framePadding, const sf::Color& bgColor, const sf::Color& tintColor)
{
    const sf::Texture* texturePtr = sprite.getTexture();
    if (!texturePtr) { return false; }
    return ::imageButtonImpl(*texturePtr, static_cast<sf::FloatRect>(sprite.getTextureRect()), size, framePadding, bgColor, tintColor);
}

/////////////// Draw_list Overloads

void DrawLine(const sf::Vector2f& a, const sf::Vector2f& b, const sf::Color& color,
    float thickness)
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    sf::Vector2f pos = ImGui::GetCursorScreenPos();
    draw_list->AddLine(a + pos, b + pos, ColorConvertFloat4ToU32(color), thickness);
}

void DrawRect(const sf::FloatRect& rect, const sf::Color& color,
    float rounding, int rounding_corners, float thickness)
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    draw_list->AddRect(
        getTopLeftAbsolute(rect),
        getDownRightAbsolute(rect),
        ColorConvertFloat4ToU32(color), rounding, rounding_corners, thickness);
}

void DrawRectFilled(const sf::FloatRect& rect, const sf::Color& color,
    float rounding, int rounding_corners)
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    draw_list->AddRectFilled(
        getTopLeftAbsolute(rect),
        getDownRightAbsolute(rect),
        ColorConvertFloat4ToU32(color), rounding, rounding_corners);
}

} // end of namespace ImGui

namespace
{

ImVec2 getTopLeftAbsolute(const sf::FloatRect & rect)
{
    ImVec2 pos = ImGui::GetCursorScreenPos();
    return ImVec2(rect.left + pos.x, rect.top + pos.y);
}
ImVec2 getDownRightAbsolute(const sf::FloatRect & rect)
{
    ImVec2 pos = ImGui::GetCursorScreenPos();
    return ImVec2(rect.left + rect.width + pos.x, rect.top + rect.height + pos.y);
}

// Rendering callback
void RenderDrawLists(ImDrawData* draw_data)
{

    if (draw_data->CmdListsCount == 0) {
        return;
    }

    ImGuiIO& io = ImGui::GetIO();
    assert(io.Fonts->TexID != NULL); // You forgot to create and set font texture

    // scale stuff (needed for proper handling of window resize)
    int fb_width = static_cast<int>(io.DisplaySize.x * io.DisplayFramebufferScale.x);
    int fb_height = static_cast<int>(io.DisplaySize.y * io.DisplayFramebufferScale.y);
    if (fb_width == 0 || fb_height == 0) { return; }
    draw_data->ScaleClipRects(io.DisplayFramebufferScale);



#ifdef GL_VERSION_ES_CL_1_1
            GLint last_program, last_texture, last_array_buffer, last_element_array_buffer;
            glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
            glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_array_buffer);
            glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &last_element_array_buffer);
#else
        glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_TRANSFORM_BIT);
#endif

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_SCISSOR_TEST);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glViewport(0, 0, (GLsizei)fb_width, (GLsizei)fb_height);

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

#ifdef GL_VERSION_ES_CL_1_1
        glOrthof(0.0f, io.DisplaySize.x, io.DisplaySize.y, 0.0f, -1.0f, +1.0f);
#else
        glOrtho(0.0f, io.DisplaySize.x, io.DisplaySize.y, 0.0f, -1.0f, +1.0f);
#endif

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (int n = 0; n < draw_data->CmdListsCount; ++n) {
        const ImDrawList* cmd_list = draw_data->CmdLists[n];
        const unsigned char* vtx_buffer = (const unsigned char*)&cmd_list->VtxBuffer.front();
        const ImDrawIdx* idx_buffer = &cmd_list->IdxBuffer.front();

        glVertexPointer(2, GL_FLOAT, sizeof(ImDrawVert), (void*)(vtx_buffer + offsetof(ImDrawVert, pos)));
        glTexCoordPointer(2, GL_FLOAT, sizeof(ImDrawVert), (void*)(vtx_buffer + offsetof(ImDrawVert, uv)));
        glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(ImDrawVert), (void*)(vtx_buffer + offsetof(ImDrawVert, col)));

        for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.size(); ++cmd_i) {
            const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
            if (pcmd->UserCallback) {
                pcmd->UserCallback(cmd_list, pcmd);
            } else {
                GLuint tex_id = (GLuint)*((unsigned int*)&pcmd->TextureId);
                glBindTexture(GL_TEXTURE_2D, tex_id);
                glScissor((int)pcmd->ClipRect.x, (int)(fb_height - pcmd->ClipRect.w),
                    (int)(pcmd->ClipRect.z - pcmd->ClipRect.x), (int)(pcmd->ClipRect.w - pcmd->ClipRect.y));
                glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, GL_UNSIGNED_SHORT, idx_buffer);
            }
            idx_buffer += pcmd->ElemCount;
        }
    }
#ifdef GL_VERSION_ES_CL_1_1
        glBindTexture(GL_TEXTURE_2D, last_texture);
            glBindBuffer(GL_ARRAY_BUFFER, last_array_buffer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, last_element_array_buffer);
            glDisable(GL_SCISSOR_TEST);
#else
        glPopAttrib();
#endif
}

bool imageButtonImpl(const sf::Texture& texture, const sf::FloatRect& textureRect, const sf::Vector2f& size, const int framePadding,
                     const sf::Color& bgColor, const sf::Color& tintColor)
{
    sf::Vector2f textureSize = static_cast<sf::Vector2f>(texture.getSize());

    ImVec2 uv0(textureRect.left / textureSize.x, textureRect.top / textureSize.y);
    ImVec2 uv1((textureRect.left + textureRect.width)  / textureSize.x,
               (textureRect.top  + textureRect.height) / textureSize.y);

    return ImGui::ImageButton((void*)texture.getNativeHandle(), size, uv0, uv1, framePadding, bgColor, tintColor);
}

} // end of anonymous namespace
