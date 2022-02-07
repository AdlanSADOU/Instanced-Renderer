#include <Vkay.h>
#include <VkayCamera.h>
#include <VkayTexture.h>
#include <VkaySprite.h>
#include <VkayInstances.h>

VkayContext  vkc;
VkayRenderer vkr;

bool   _bQuit       = false;
Color  _clear_color = Color(.33f, .33f, .33f, 1.f);
Camera _camera;

InstanceBucket _bucket;
Sprite _sprite;
Texture _texture;

// SDL complains if char const *argv[]
int main(int argc, char *argv[])
{
    VkayContextInit(&vkc);
    VkayRendererInit(&vkc, &vkr);
    VkayCameraCreate(&vkr, &_camera);

    // VkayTextureCreate();
    // _bucket.AddSpriteInstance()

    while (!_bQuit) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            SDL_Keycode key = e.key.keysym.sym;
            if (e.type == SDL_QUIT)
                _bQuit = true;
            if (e.type == SDL_KEYUP) {
                if (key == SDLK_ESCAPE)
                    _bQuit = true;
            }
        }

        VkayRendererBeginCommandBuffer(&vkr);
        VkayRendererBeginRenderPass(&vkr);

        VkayRendererClearColor(&vkr, _clear_color);
        VkayCameraUpdate(&vkr, &_camera, vkr.instanced_pipeline_layout);

        VkayRendererEndRenderPass(&vkr);
        VkayRendererEndCommandBuffer(&vkr);
        VkayRendererPresent(&vkr);
    }

    VkayCameraDestroy(&vkr, &_camera);
    VkayRendererCleanup(&vkr);
    VkayContextCleanup(&vkc);

    return 0;
}