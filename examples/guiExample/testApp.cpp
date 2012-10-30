//--------------------------------------------------------------

#include "testApp.h"

//--------------------------------------------------------------

void testApp::setup()
{
    ofBackground(0, 0, 0);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);

    rotation    = 0.0f;
    distance    = 50.0f;
    size                = 100.0f;
    edges               = 20.0f;

    position    = ofVec2f(320.0f, 240.0f);

    animate1    = kofxGui_Button_Off;
    animate2    = false;

    speed1              = 0.0f;
    speed2              = 0.0f;
    speed3              = 0.0f;

    color1              = ofRGBA(0xFF0000FF);
    color2              = ofRGBA(0x00FF00FF);
    color3              = ofRGBA(0x0000FFFF);

    matrix              = NULL;
    matrixX             = 7;
    matrixY             = 7;
    matrixSize  = matrixX * matrixY;
    matrixId    = -1;

    gui = ofxGui::Instance(this);

    if(!gui->buildFromXml(OFXGUI_XML))
    {
        ofxGuiPanel* panel1 = gui->addPanel(kParameter_Panel1, "properties", 10, 10, OFXGUI_PANEL_BORDER, OFXGUI_PANEL_SPACING);
        panel1->addSlider(kParameter_Rotation, "rotation", 110, OFXGUI_SLIDER_HEIGHT, 0.0f, 360.0f, rotation, kofxGui_Display_Float4, 0);
        panel1->addSlider(kParameter_Distance, "distance", 110, OFXGUI_SLIDER_HEIGHT, 10.0f, 100.0f, distance, kofxGui_Display_Int, 0);
        panel1->addSlider(kParameter_Size, "size", 110, OFXGUI_SLIDER_HEIGHT, 10.0f, 500.0f, size, kofxGui_Display_Int, 0);
        panel1->addSlider(kParameter_Edges, "edges", 110, OFXGUI_SLIDER_HEIGHT, 0.0f, 40.0f, edges, kofxGui_Display_Int, 10);
        panel1->addColor(kParameter_Color1, "color1", 110, OFXGUI_COLOR_HEIGHT, color1, kofxGui_Color_RGB);
        panel1->addColor(kParameter_Color2, "color2", 110, OFXGUI_COLOR_HEIGHT, color2, kofxGui_Color_RGB);
        panel1->addColor(kParameter_Color3, "color3", 110, OFXGUI_COLOR_HEIGHT, color3, kofxGui_Color_RGB);

        ofxGuiPanel* panel2 = gui->addPanel(kParameter_Panel2, "files", 10, 380, OFXGUI_PANEL_BORDER, OFXGUI_PANEL_SPACING);
        panel2->addFiles(kParameter_File, "files", 110, OFXGUI_FILES_HEIGHT, "", "", "xml");
        panel2->addButton(kParameter_SaveXml, "saveToXml", OFXGUI_BUTTON_HEIGHT, OFXGUI_BUTTON_HEIGHT, kofxGui_Button_Off, kofxGui_Button_Trigger);

        ofxGuiPanel* panel3 = gui->addPanel(kParameter_Panel3, "animation", 495, 10, OFXGUI_PANEL_BORDER, OFXGUI_PANEL_SPACING);
        panel3->addXYPad(kParameter_Position, "position", 110, 82, ofVec2f(0.0f, 0.0f), ofVec2f(640.0f, 480.0f), position, kofxGui_Display_Int, 0);
        panel3->addPoints(kParameter_Points1, "points1", 110, 82, ofVec2f(0.0f, 0.0f), ofVec2f(640.0f, 480.0f), position, kofxGui_Display_Int, 0);
        panel3->addSlider(kParameter_Speed1, "speed1", 110, OFXGUI_SLIDER_HEIGHT, 0.0f, 0.01f, speed1, kofxGui_Display_Float4, 0);
        panel3->addPoints(kParameter_Points2, "points2", 110, 82, ofVec2f(0.0f, 0.0f), ofVec2f(360.0f, 360.0f), ofVec2f(180.0f, 180.0f), kofxGui_Display_Int, 0);
        panel3->addSlider(kParameter_Speed2, "speed2", 110, OFXGUI_SLIDER_HEIGHT, 0.0f, 0.01f, speed2, kofxGui_Display_Float4, 0);
        panel3->addButton(kParameter_Animate, "animate", OFXGUI_BUTTON_HEIGHT, OFXGUI_BUTTON_HEIGHT, animate1, kofxGui_Button_Switch);

        ofxGuiPanel* panel4 = gui->addPanel(kParameter_Panel4, "monome", 155, 10, OFXGUI_PANEL_BORDER, OFXGUI_PANEL_SPACING);
        panel4->addMatrix(kParameter_Matrix, "matrix", 110, 110, matrixX, matrixY, matrixId, kofxGui_Button_Switch, OFXGUI_MATRIX_SPACING);
        panel4->addKnob(kParameter_Speed3, "time", 60, 60, 0.0f, 0.05f, speed3, kofxGui_Display_Float4, 0);
        panel4->addSwitch(kParameter_Mode, "mode", 110, OFXGUI_SLIDER_HEIGHT, 0, 2, 0, &dummy_Tags[0]);

        //      do update while inactive
        gui->forceUpdate(true);
    }

    //  reset animate counter
    ticks1 = 0.0f;
    ticks2 = 0.0f;
    ticks3 = 0.0f;
}

//--------------------------------------------------------------

void testApp::update()
{
    ticks1 += speed1;

    if(ticks1 > 1.0f)
        ticks1 -= 1.0f;

    ticks2 += speed2;

    if(ticks2 > 1.0f)
        ticks2 -= 1.0f;

    ticks3 += speed3;

    if(ticks3 > 1.0f)
        ticks3 -= 1.0f;

    //lets make our circles look a little nicer!
    ofSetCircleResolution(edges);

    //---------------------------
    // update the UI

    if(animate1)
    {
        gui->update(kParameter_Points1, kofxGui_Set_Float, &ticks1, sizeof(float));
        gui->update(kParameter_Points2, kofxGui_Set_Float, &ticks2, sizeof(float));
    }

    if(matrixMode > 0)
    {
        //      show some action in the matrix view
        //      gui->update(kParameter_Matrix, kofxGui_Set_Float, &ticks3, sizeof(float));

        int id = (int)(CLAMP(ticks3, 0.0f, 1.0f) * matrixX);

        if(id == matrixId)
            return;

        matrixId = id;

        for(int i = 0; i < matrixY; i++)
        {
            for(int j = 0; j < matrixX; j++)
            {
                int index       = j + (i * matrixX);
                int     active  = matrixMode == 1 ? j : i;

                matrix[index] &= kofxGui_Matrix_Set;

                if(active == matrixId)
                    matrix[index] |= kofxGui_Matrix_Selected;
            }
        }
    }
}

//--------------------------------------------------------------

void testApp::draw()
{
    //Lets enable blending!
    //We are going to use a blend mode that adds
    //all the colors to white.
    ofEnableAlphaBlending();
    glBlendFunc(GL_SRC_COLOR, GL_ONE);

    //---------------------------------
    //RGB CICRLES

    //We only want to rotate the circles
    //So we use push and pop matrix to
    //make sure the rotation is contained
    glPushMatrix();
    //we position the rotation point
    //at the location we want it to
    //spin around .
    glTranslatef(position.x, position.y, 0);
    glRotatef(rotation, 0, 0, 1);

    ofFill();

    //draw a red circle
    //ofSetColor(255,0, 0);
    glColor4f(color1.r, color1.g, color1.b, color1.a);
    ofCircle(-distance, -(distance / 2), size);

    //draw a green circle
    glColor4f(color2.r, color2.g, color2.b, color2.a);
    ofCircle(distance, -(distance / 2), size);

    //draw a blue circle
    glColor4f(color3.r, color3.g, color3.b, color3.a);
    ofCircle(0, distance, size);
    glPopMatrix();

    //Lets stop the blending!
    ofDisableAlphaBlending();

    gui->draw();
}

//--------------------------------------------------------------

void testApp::keyPressed(int key)
{
    if(key == 112)
        gui->activate(!gui->mIsActive);
    if (key == OF_KEY_ESC)
    {
        exitApp();
    }
}

//--------------------------------------------------------------

void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------

void testApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------

void testApp::mouseDragged(int x, int y, int button)
{
    gui->mouseDragged(x, y, button);
}

//--------------------------------------------------------------

void testApp::mousePressed(int x, int y, int button)
{
    gui->mousePressed(x, y, button);
}

//--------------------------------------------------------------

void testApp::mouseReleased()
{
    gui->mouseReleased(mouseX, mouseY, 0);
}

//--------------------------------------------------------------

void testApp::handleGui(int parameterId, int task, void* data, int length)
{
    switch(parameterId)
    {
    case kParameter_Panel1:
    case kParameter_Panel2:
        break;

    case kParameter_Rotation:
        if(task == kofxGui_Set_Float)
            rotation = *(float*)data;
        break;

    case kParameter_Distance:
        if(task == kofxGui_Set_Float)
            distance = *(float*)data;
        break;

    case kParameter_Size:
        if(task == kofxGui_Set_Float)
            size = *(float*)data;
        break;

    case kParameter_Edges:
        if(task == kofxGui_Set_Float)
            edges = *(float*)data;
        break;

    case kParameter_Color1:
        if(task == kofxGui_Set_Color)
            color1 = *(ofRGBA*)data;
        break;

    case kParameter_Color2:
        if(task == kofxGui_Set_Color)
            color2 = *(ofRGBA*)data;
        break;

    case kParameter_Color3:
        if(task == kofxGui_Set_Color)
            color3 = *(ofRGBA*)data;
        break;

    case kParameter_File:
        if(task == kofxGui_Set_String)
        {
            string file = *(string*)data;
            gui->buildFromXml(file);
        }
        break;

    case kParameter_SaveXml:
        if(task == kofxGui_Set_Bool)
        {
            if(*(bool*)data)
                gui->saveToXml(OFXGUI_XML);
        }
        break;

    case kParameter_Position:
        if(task == kofxGui_Set_Point)
            position = *(ofVec2f*)data;
        break;

    case kParameter_Points1:
        if(task == kofxGui_Set_Point)
            position = *(ofVec2f*)data;
        break;

    case kParameter_Speed1:
        if(task == kofxGui_Set_Float)
            speed1 = *(float*)data;
        break;

    case kParameter_Points2:
        if(task == kofxGui_Set_Point)
            rotation = (*(ofVec2f*)data).y;
        break;

    case kParameter_Speed2:
        if(task == kofxGui_Set_Float)
            speed2 = *(float*)data;
        break;

    case kParameter_Animate:
        if(task == kofxGui_Set_Bool)
            animate1 = *(bool*)data;
        break;

    case kParameter_Matrix:
        if(task == kofxGui_Set_Cell)
        {
            //  ofCell cell = *(ofCell*)data;
        }
        else if(task == kofxGui_Set_IntArray)
        {
            matrix              = (int*)data;
            matrixSize  = length;
        }
        break;

    case kParameter_Speed3:
        if(task == kofxGui_Set_Float)
            speed3 = *(float*)data;
        break;

    case kParameter_Mode:
        if(task == kofxGui_Set_Int)
            matrixMode = *(int*)data;
        break;
    }
}

//--------------------------------------------------------------
