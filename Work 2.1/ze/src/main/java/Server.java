import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {

    public void run(int porta) {
        ObjectOutputStream output;
        ObjectInputStream input;
        boolean sair = false;
        String mensagem = "";

        try {
            ServerSocket servidor = new ServerSocket(porta);
            Socket conexao;
            while (!sair) {
                System.out.println("Esperando conexão " + porta);

                conexao = servidor.accept();

                System.out.println(conexao.getInetAddress().getHostAddress() + " conectado");

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
        Server s = new Server();
        s.run(porta);
    }
}
