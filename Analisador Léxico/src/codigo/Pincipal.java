/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package codigo;

import java.io.File;

/**
 *
 * @author Windows
 */
public class Pincipal {
    public static void main(String[] args) {
        String path="C:/Users/Windows/Desktop/Engenharia da Computação/8° Período/Compiladores/Trabalho Final/analisador_lexico/src/codigo/Lexer.flex";
        gerar_lexer(path);
    }
    
    public static void gerar_lexer(String path){
        File arquivo=new File(path);
        JFlex.Main.generate(arquivo);
    }
}
