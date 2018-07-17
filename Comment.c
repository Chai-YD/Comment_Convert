#include<stdio.h>
#include<stdlib.h>
typedef enum State{
    NORMAL,       //普通状态
    FOUND_SLASH,  //遇到/状态
    CPP_COMMENT,  //c++注释状态
    C_COMMENT,    //c注释状态  
    FOUND_STAR,  //遇到*状态
}State;
void CommentConvert(FILE* input,FILE* output){
    State state = NORMAL;
    char ch;
    char next;
    while(1){
        ch = fgetc(input);
        if(ch == EOF){
            return;
        }
        switch(state){
            case NORMAL:
                if(ch == '/'){
                    fputc('/',output);
                    state = FOUND_SLASH;
                }else{
                    fputc(ch,output);
                    state = NORMAL;
                }
                break;
            case FOUND_SLASH:
                if(ch == '*'){
                    fputc('/',output);
                    state = C_COMMENT;
                }else if(ch == '/'){
                    fputc('/',output);
                    state = CPP_COMMENT;
                }else{
                    fputc(ch,output);
                    state = NORMAL;
                }
                break;
            case CPP_COMMENT:
                if(ch == '\n'){
                    fputc('\n',output);
                    state = NORMAL;
                }else{
                    fputc(ch,output);
                    state = CPP_COMMENT;
                }
                break;
            case C_COMMENT:
                if(ch == '*'){
                   state = FOUND_STAR;
                }else if(ch == '\n'){
                    fputc('\n',output);
                    fputc('/',output);
                    fputc('/',output);
                }else{
                    fputc(ch,output);
                    state = C_COMMENT;
                }
                break;
            case FOUND_STAR:
                if(ch == '*'){
                    fputc('*',output);
                    state = FOUND_STAR;
                }else if(ch == '/'){
                    next = fgetc(input);
                    ungetc(next,input);
                    if(next != '\n'){
                        fputc('\n',output);
                        state = NORMAL;
                    }else{
                        state = NORMAL;
                    }
                }else{
                    fputc('*',output);
                    fputc(ch,output);
                    state = C_COMMENT;
                }
                break;

        }
    }
}
    int main(){
        FILE* input = fopen("input.c","r");
        FILE* output = fopen("output.c","w");
        CommentConvert(input,output);
        fclose(output);
        fclose(input);
        return 0;
}
