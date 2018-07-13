#include "UI.h"

int main()
{
    UI::Init();
    while(appletMainLoop())
    {
        UI::Loop();
    }
    UI::Exit();
    return 0;
}

int miniVideo()
{
    gfxInitDefault();
    consoleInit(NULL);
    Result rst;
    MediaFile_t *vid;
    rst = minivideo_open("sdmc:/video.mp4", &vid);
    if(rst == 1)
    {
        rst = minivideo_parse(vid, false);
        if(rst == 1)
        {
            int dur = vid->duration;
            cout << " *** Video duration: " << dur / 1000 << " seconds" << endl;
            rst = minivideo_thumbnail(vid, "sdmc:/", PICTURE_JPG, 75, 1, 0);
            if(rst == 1)
            {
                cout << " *** Extracting done!" << endl;
                rst = minivideo_close(&vid);
                if(rst == 1)
                {
                    cout << " *** Closed!" << endl;
                }
                else cout << " *-* Closing error!" << endl;
            }
            else cout << " *-* Extracting error!" << endl;
        }
        else cout << " *-* Parse error!" << endl;
    }
    else cout << " *-* Open error!" << endl;
    while(appletMainLoop())
    {
        gfxFlushBuffers();
        gfxSwapBuffers();
        gfxWaitForVsync();
        hidScanInput();
        int k = hidKeysDown(CONTROLLER_P1_AUTO);
        if(k & KEY_A) break;
    }
    gfxExit();
    return 0; 
}