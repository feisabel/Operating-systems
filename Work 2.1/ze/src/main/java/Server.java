import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class Server extends Thread {
    private Socket conexao;

    public Server(Socket s){
        conexao = s;
    }

    public void run() {
        ObjectOutputStream output;
        ObjectInputStream input;
        boolean sair = false;
        String mensagem = "";

        try {
            while (!sair) {
                output = new ObjectOutputStream(conexao.getOutputStream());
                input = new ObjectInputStream(conexao.getInputStream());

                do {
                    try {
                        mensagem = (String) input.readObject();
                        System.out.println("Cliente>> " + mensagem);
                        output.writeObject(mensagem);
                    } catch (IOException iOException) {
                        System.err.println("erro: " + iOException.toString());
                    }
                } while (!mensagem.equals("DF"));

                System.out.println("Conexao encerrada pelo cliente");
                sair = true;
                output.close(); input.close();
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
