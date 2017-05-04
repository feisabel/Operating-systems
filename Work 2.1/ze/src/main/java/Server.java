import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class Server extends Thread {
    private Socket conexao;
    private Ze ze;

    private void update(String msg){
        Scanner s = new Scanner(msg).useDelimiter(",");
        ze.updateRun(s.nextInt());
        ze.checkJump(s.nextInt());
        ze.checkArm(s.nextInt());
        ze.clearScreen();
        ze.draw();
    }

    public Server(Socket s, Ze ze){
        conexao = s;
        this.ze = ze;
    }

    public static String getString( InputStream is) throws IOException {
        int ch;
        StringBuilder sb = new StringBuilder();
        while((ch = is.read()) != '\0')
            sb.append((char)ch);
        return sb.toString();
    }

    public void run() {
        DataInputStream input;
        boolean sair = false;

        try {
            input = new DataInputStream(conexao.getInputStream());
            String result = "";
            try {
                   result = getString(input);
                   update(result);
            } catch (IOException iOException) {
                System.err.println("Erro lendo mensagem: " + iOException.toString());
            }

            System.out.println("Conexao encerrada pelo cliente");
            input.close();
            conexao.close();
        } catch (Exception e) {
            System.err.println("Erro: " + e.toString());
        }
    }

    public static void main(String[] args) {
        int porta = 4325;
        Ze ze = new Ze();
        try{
            ServerSocket s = new ServerSocket(porta);
            while(true){
                //System.out.println("Esperando conexão " + porta);
                Socket conexao = s.accept();
                //System.out.println(conexao.getInetAddress().getHostAddress() + " conectado");
                Thread t = new Server(conexao, ze);
                t.start();
            }
        }catch (IOException e){
            System.err.println("erro: " + e.toString());
        }
    }
}
