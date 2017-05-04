import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class Server extends Thread {
    private Socket conexao;

    public Server(Socket s){
        conexao = s;
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
            while(!sair){
                input = new DataInputStream(conexao.getInputStream());
                String result = "";
                do{
                    try {
                       result = getString(input);
                       System.out.println("Cliente>> " + result);
                   } catch (IOException iOException) {
                        System.err.println("Erro lendo mensagem: " + iOException.toString());
                    }
                } while(!result.equals("DF"));

                System.out.println("Conexao encerrada pelo cliente");
                input.close();
                conexao.close();
            }
        } catch (Exception e) {
            System.err.println("Erro: " + e.toString());
        }
    }

    public static void main(String[] args) {
        int porta = 4325;
        try{
            ServerSocket s = new ServerSocket(porta);
            while(true){
                System.out.println("Esperando conexão " + porta);
                Socket conexao = s.accept();
                System.out.println(conexao.getInetAddress().getHostAddress() + " conectado");
                Thread t = new Server(conexao);
                t.start();
            }
        }catch (IOException e){
            System.err.println("erro: " + e.toString());
        }
    }
}
