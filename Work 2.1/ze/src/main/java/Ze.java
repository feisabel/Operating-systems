
public class Ze {
    protected boolean jump;
    protected boolean arm;
    protected boolean running;
    protected int n, m, pot_atual;

    public Ze (){
        jump = false;
        arm = false;
        running = true;
        n = 20;
        m = 20;
        pot_atual = 2048;

    }

    public static void clearScreen() {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }

    void updateRun(int pot){
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
    }

    void checkJump(int btn){
        if (btn == 1){
            jump = (!jump) ? true : false;
        }
    }

    void checkArm(int ldr){
        if (ldr < 1000) {
            arm = (!arm) ? true : false;
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
