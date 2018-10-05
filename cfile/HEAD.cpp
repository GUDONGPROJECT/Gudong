/*
 * 基类Button
 */

 /*****************************************************
 Function：     Button::Button

 Description:   Button的构造函数

 Input:         int xx1     Button左上角横坐标
                int yy1     Button左上角纵坐标
                int xx2     Button右下角横坐标
                int yy2     Button右下角纵坐标
                char *n     Button的名称
                char *Fun   点击Button后触发的事件的函数接口

 Output:        NULL

 Return:        NULL
 ****************************************************/
Button::Button(int xx1,int yy1,int xx2,int yy2,char *Fun=Null, char *n=Null){
    x1=xx1;
    y1=yy1;
    x2=xx2;
    y2=yy2;
    fun=Fun;
    name=n;
}

/*****************************************************
 Function：     Button::IsClick

 Description:   判断Button是否被点击

 Input:         MOUSE *mouse    鼠标点击时鼠标的状态

 Output:        NULL

 Return:        是否被点击
 ****************************************************/
bool IsClick(MOUSE *mouse){
    if(mouse.pos_y<y2&&mouse.pos_y>y1&&mouse.pos_x>x2&&mouse.pos_x<x1){
        OnClick();
        return true;
    }
    else
        return false;
}

/*****************************************************
 Function：     Button::Show

 Description:   显示Button

 Input:         NULL

 Output:        按钮

 Return:        NULL
 ****************************************************/
virtual void Button::Show(void){
    dis_16hz((x1+x2)/2-strlen(name)*8,(y1+y2)/2-8,name,BLACK)
}

/*****************************************************
 Function：     Button::OnClick

 Description:   Button点击响应

 Input:         NULL

 Output:        Button点击响应事件

 Return:        NULL
 ****************************************************/
virtual void Button::OnClick(void){;}









/*
 * SmallButton类
 */

/*****************************************************
 Function：     Simple::Simple

 Description:   构造Simplea按钮

 Input:         int xx1     Button左上角横坐标
                int yy1     Button左上角纵坐标
                int xx2     Button右下角横坐标
                int yy2     Button右下角纵坐标
                char *n     Button的名称
                char *Fun   点击Button后触发的事件的函数接口

 Output:        Button点击响应事件

 Return:        NULL
 ****************************************************/
Simple::Simple(int xx1,int yy1,int xx2,int yy2,char *Fun=Null, char *n=Null){
    x1=xx1;
    y1=yy1;
    x2=xx2;
    y2=yy2;
    fun=Fun;
    name=n;
}

/*****************************************************
 Function：     Button::OnClick

 Description:   Button点击响应

 Input:         NULL

 Output:        Button点击响应事件

 Return:        NULL
 ****************************************************/
void Simple::Show(void){
    float size=5.5;
    int y=(y1+y2)/2;
    dis_16hz(4*size,y-8,name,BLACK);
    SVGA_Line(64*size,y,63*size,y-size,LIGHT_GRAY);
    SVGA_Line(64*size,y,63*size,y+size,LIGHT_GRAY);
    SVGA_Line(4*size,y2,68*size,y2,LIGHT_GRAY);
}
/*****************************************************
 Function：     Button::OnClick

 Description:   Button点击响应

 Input:         NULL

 Output:        Button点击响应事件

 Return:        NULL
 ****************************************************/
void Onclick(void){;}