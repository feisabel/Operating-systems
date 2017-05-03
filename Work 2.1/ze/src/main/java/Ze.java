
public class Ze {
    boolean jump = false;
    boolean arm = false;
    boolean running = true;
    int n = 20;
    int m = 20;
    int pot_atual = 2048;

    public static void clearScreen() {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }

    void updateRun(int pot){
        while (running){
            if (pot > pot_atual + 10){
                pot_atual = pot;
                if (n > 0){
                    n--; m++;
                }
            } else if (pot < pot_atual - 10){
                pot_atual = pot;
                if (m > 0){
                    m--; n++;
                }
            }
            clearScreen();
            draw();
            //TODO: thread sleep
        }
    }

    void checkJump(int btn){
        while(running){
            if (btn == 1){
                jump = true;
                draw();
                //TODO: sleep
                jump = false;
            }
            clearScreen();
            draw();
            //TODO: SLEEP thread
        }
    }

    void checkArm(int ldr){
        while (running){
            if (ldr < 1000) {
                arm = true;
                clearScreen();
                draw();
                //sleep
                arm = false;
            }
            clearScreen();
            draw();
            //TODO: thread sleep
        }
    }

    public void draw(){
        String s1;
        String s2;
        String output;
        output = (!jump) ? "\r\n\n\n\n\n\n" : "\r\n\n\n";
        System.out.println(output);
        s1 = "";
        s2 = "";
        for(int i = 0; i < n; i++) {
            s1 += " ";
        }
        for(int i = 0; i < m; i++) {
            s2 += " ";
        }
        output = (!arm) ? (s1 + " o " + s2 + "\n" + s1 + "`|´" + s2 + "\n" + s1 + " ^ " + s2) : (s1 + " o " + s2 + "\n" + s1 + "`|," + s2 + "\n" + s1 + " ^ " + s2);
        System.out.println(output);
        if (jump){
            System.out.println("\n\n");
        }
    }
}
