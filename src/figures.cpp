#include "figure.h"



class j_figure : public Figure{
public:
    j_figure(): Figure(){
        fig[1][0] = fig[1][1] = fig[1][2] = fig[2][2] = 1;
    }
    int rotate(){
        return 0;
    }
    
};



class l_figure : public Figure{
public:
    l_figure(): Figure(){
        fig[1][0] = fig[1][1] = fig[1][2] = fig[2][0] = 1;
    };
    int rotate(){
        return 0;
    }
};

class t_figure : public Figure{
public:
    t_figure(): Figure(){
        fig[1][0] = fig[1][1] = fig[1][2] = fig[2][1] = 1;
    };
    int rotate(){
        return 0;
    }
};

class s_figure : public Figure{
public:
    s_figure(): Figure(){
        fig[1][1] = fig[1][2] = fig[2][0] = fig[2][1] = 1;
    };
    int rotate(){
        return 0;
    }
};

class z_figure : public Figure{
public: 
    z_figure() : Figure(){
        fig[1][0] = fig[1][1] = fig[2][1] = fig[2][2] = 1;
    };
    int rotate(){
        return 0;
    }
};

class o_figure : public Figure{
public:
    o_figure() : Figure(){
        fig[1][1] = fig[1][2] = fig[2][1] = fig[2][2] = 1;
    };
    int rotate(){
        return 0;
    }
};

class i_figure : public Figure{
public:
    i_figure() : Figure(){
        fig[1][0] = fig[1][1] = fig[1][2] = fig[1][3] = 1;
    };
    int rotate(){
        return 0;
    }
};
