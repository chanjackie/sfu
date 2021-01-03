package sample;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Pos;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.stage.Stage;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

public class Main extends Application {

    public static void getStatus(Label label) {
        try {
            URL statusUrl = new URL("http://bobbystesla.me/api/status");
            HttpURLConnection statusConnection = (HttpURLConnection) statusUrl.openConnection();
            statusConnection.setRequestMethod("GET");
            statusConnection.getInputStream();
            BufferedReader br = new BufferedReader(new InputStreamReader(statusConnection.getInputStream()));
            label.setText("Currently: " + br.readLine());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void start(Stage primaryStage) throws Exception{
        primaryStage.setTitle("My Tesla");
        Button toggleBtn = new Button("Toggle");
        Label stateLabel = new Label("Currently: unknown");

        getStatus(stateLabel);

        VBox vb = new VBox(10, stateLabel, toggleBtn);
        vb.setAlignment(Pos.CENTER);

        toggleBtn.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent actionEvent) {
                try {
                    URL url = new URL("http://bobbystesla.me/api/toggle");
                    HttpURLConnection connection = (HttpURLConnection) url.openConnection();
                    connection.setRequestMethod("POST");
                    if (connection.getResponseCode() == 200) {
                        getStatus(stateLabel);
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        primaryStage.setScene(new Scene(vb, 300, 200));
        primaryStage.show();
    }


    public static void main(String[] args) {
        launch(args);
    }
}
