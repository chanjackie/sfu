package ca.cmpt213.asn5.client;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

public class Main extends Application {

    @Override
    public void start(Stage primaryStage) throws Exception{
        primaryStage.setTitle("Tokimon Collector");

        Button btn = new Button("Get Tokimons");
        Label tokiLabel = new Label("");

        VBox vb = new VBox(20, btn, tokiLabel);

        btn.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent actionEvent) {
                try {
                    URL url = new URL("http://localhost:8080/api/tokimon/all");
                    HttpURLConnection connection = (HttpURLConnection) url.openConnection();
                    connection.setRequestMethod("GET");

                    connection.getInputStream();
                    BufferedReader br = new BufferedReader(new InputStreamReader(connection.getInputStream()));

                    tokiLabel.setText(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        primaryStage.setScene(new Scene(vb, 800, 600));
        primaryStage.show();
    }


    public static void main(String[] args) {
        launch(args);
    }
}
