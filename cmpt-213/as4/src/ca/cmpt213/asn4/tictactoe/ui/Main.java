package ca.cmpt213.asn4.tictactoe.ui;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Pos;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;


public class Main extends Application {

    public static final String PATH_TO_X_IMAGE = "https://www.pngkit.com/png/full/205-2056266_player-o-into-tic-tac-toe-img-tic.png";
    public static final String PATH_TO_O_IMAGE = "https://www.pngkey.com/png/full/205-2056274_tic-tac-toe-img-letter-o.png";
    public static final String PATH_TO_EMPTY_SQUARE = "file:img/square.png";

    @Override
    public void start(Stage primaryStage) throws Exception {
        Label winnerLabel = new Label("");
        Button newGameButton = new Button("New Game");

        GridPane gridpane = createGridpaneBoard();

        VBox vbox = new VBox(10, gridpane, winnerLabel, newGameButton);
        vbox.setAlignment(Pos.CENTER);

        primaryStage.setTitle("TicTacToe");
        primaryStage.setScene(new Scene(vbox, 450, 500));
        primaryStage.show();
    }

    private GridPane createGridpaneBoard() {
        ImageView image11 = new ImageView(new Image(PATH_TO_EMPTY_SQUARE));
        ImageView image12 = new ImageView(new Image(PATH_TO_EMPTY_SQUARE));
        ImageView image13 = new ImageView(new Image(PATH_TO_EMPTY_SQUARE));
        ImageView image14 = new ImageView(new Image(PATH_TO_EMPTY_SQUARE));
        ImageView image21 = new ImageView(new Image(PATH_TO_EMPTY_SQUARE));
        ImageView image22 = new ImageView(new Image(PATH_TO_EMPTY_SQUARE));
        ImageView image23 = new ImageView(new Image(PATH_TO_EMPTY_SQUARE));
        ImageView image24 = new ImageView(new Image(PATH_TO_EMPTY_SQUARE));
        ImageView image31 = new ImageView(new Image(PATH_TO_EMPTY_SQUARE));
        ImageView image32 = new ImageView(new Image(PATH_TO_EMPTY_SQUARE));
        ImageView image33 = new ImageView(new Image(PATH_TO_EMPTY_SQUARE));
        ImageView image34 = new ImageView(new Image(PATH_TO_EMPTY_SQUARE));
        ImageView image41 = new ImageView(new Image(PATH_TO_EMPTY_SQUARE));
        ImageView image42 = new ImageView(new Image(PATH_TO_EMPTY_SQUARE));
        ImageView image43 = new ImageView(new Image(PATH_TO_EMPTY_SQUARE));
        ImageView image44 = new ImageView(new Image(PATH_TO_EMPTY_SQUARE));

        GridPane gridpane = new GridPane();
        gridpane.add(image11, 0, 0);
        gridpane.add(image12, 0, 1);
        gridpane.add(image13, 0, 2);
        gridpane.add(image14, 0, 3);
        gridpane.add(image21, 1, 0);
        gridpane.add(image22, 1, 1);
        gridpane.add(image23, 1, 2);
        gridpane.add(image24, 1, 3);
        gridpane.add(image31, 2, 0);
        gridpane.add(image32, 2, 1);
        gridpane.add(image33, 2, 2);
        gridpane.add(image34, 2, 3);
        gridpane.add(image41, 3, 0);
        gridpane.add(image42, 3, 1);
        gridpane.add(image43, 3, 2);
        gridpane.add(image44, 3, 3);

        gridpane.setVgap(2);
        gridpane.setHgap(2);

        return gridpane;
    }


    public static void main(String[] args) {
        launch(args);
    }
}
