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
};

class o_figure : public Figure{
public:
    o_figure() : Figure(){
        fig[1][1] = fig[1][2] = fig[2][1] = fig[2][2] = 1;
    };
    int rotate(Matrix &m){
        return 0;
    }
};

class i_figure : public Figure{
private:
    int position;
public:
    i_figure() : Figure(){
        fig[1][0] = fig[1][1] = fig[1][2] = fig[1][3] = 1;
        position = 0;
    };
    int rotate(Matrix &m){
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                fig_copy[i][j] = 0;
            }
        }
        if(position == 0){
            fig_copy[0][1] = fig_copy[1][1] = fig_copy[2][1] = fig_copy[3][1] = 1;
            position = 1;
        }
        else if(position == 1){
            fig_copy[1][0] = fig_copy[1][1] = fig_copy[1][2] = fig_copy[1][3] = 1;
            position = 0;
        }

        if(check_if_able_rotate(m)){
            for (int i = 0; i < 4; i++){
                for (int j = 0; j < 4; j++){
                    fig[i][j] = fig_copy[i][j];
                }
            }
        //fig = fig_copy;
            return 1;
        }
        else{
            return 0;
        }
       
    }
};
