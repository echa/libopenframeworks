//--------------------------------------------------------------

#ifndef _TEST_APP
#define _TEST_APP

//--------------------------------------------------------------

#include <ofMain.h>
#include <ofxXmlSettings.h>

#include <ofxGui.h>
#include <ofxGuiTypes.h>

//--------------------------------------------------------------

const string dummy_Tags[] =
    {
        "off",
        "vertical",
        "horizontal"
    };

//--------------------------------------------------------------

class testApp : public ofSimpleApp, public ofxGuiListener
{
    enum
    {
        kParameter_Panel1,
        kParameter_Panel2,
        kParameter_Panel3,
        kParameter_Panel4,

        kParameter_Rotation,
        kParameter_Distance,
        kParameter_Size,
        kParameter_Position,
        kParameter_Edges,
        kParameter_Animate,
        kParameter_SaveXml,
        kParameter_Speed1,
        kParameter_Speed2,
        kParameter_Points1,
        kParameter_Points2,
        kParameter_File,
        kParameter_Color1,
        kParameter_Color2,
        kParameter_Color3,
        kParameter_Matrix,
        kParameter_Speed3,
        kParameter_Mode
    };

 public:

    void                setup();
    void                update();
    void                draw();

    void                keyPressed(int key);
    void                keyReleased(int key);
    void                mouseMoved(int x, int y );
    void                mouseDragged(int x, int y, int button);
    void                mousePressed(int x, int y, int button);
    void                mouseReleased();

    void                handleGui(int parameterId, int task, void* data, int length);

    float               rotation;
    float               distance;
    float               size;
    ofVec2f             position;
    float               edges;
    float               ticks1, ticks2, ticks3;
    bool                animate1, animate2;
    float               speed1, speed2, speed3;
    ofRGBA              color1, color2, color3;

    int*                matrix;
    int                 matrixX, matrixY, matrixSize, matrixId, matrixMode;

    ofxGui*             gui;
};

//--------------------------------------------------------------

#endif

//--------------------------------------------------------------
