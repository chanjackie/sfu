/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package asn7;

import java.sql.*;

/**
 *
 * @author jgc11
 */
public class ConSingleton {

    private static ConSingleton instance = null;

    private String username;
    private String password;
    private Connection con;
    private String errorMessage;

    private PreparedStatement pstmt;
    private ResultSet rs;
    
    private SearchListingsUI previousSearch;
    private ReviewUI previousReview;
    private boolean comingFromUI = false;
    private int listingId;

    private ConSingleton() {
        
    }

    public static ConSingleton getInstance() {
        if (instance == null) {
            instance = new ConSingleton();
        }
        return instance;
    }
    
    public boolean connect(String user, String pass) {
        String connectionUrl = "jdbc:sqlserver://cypress;"
                + "user = " + user + ";"
                + "password = " + pass;
        try {
            Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
        } catch (ClassNotFoundException ce) {
            System.out.println("\n\nNo JDBC Driver for SQL Server; exit now.\n\n");
            return false;
        }

        try {
            this.con = DriverManager.getConnection(connectionUrl);
        } catch (SQLException se) {
            System.out.println("\n\nFail to connect to CSIL SQL Server; exit now.\n\n");
            System.out.println(se.toString());
            destroy();
            return false;
        }
        this.username = user;
        this.password = pass;
        return true;
    }

    public String getUsername() {
        return username;
    }

    public Connection getConnection() {
        return con;
    }

    public ResultSet query(String query) {
        if (username == null || password == null || con == null) {
            return null;
        }
        try {
            this.pstmt = con.prepareStatement(query);
            rs = pstmt.executeQuery();
        } catch (SQLException se) {
            System.out.println("\nSQL Exception occurred, the state : "
                    + se.getSQLState() + "\nMessage:\n" + se.getMessage() + "\n");
            this.errorMessage = se.getMessage();
            return null;
        }
        return rs;
    }
    
    public boolean update(String statement) {
        if (username == null || password == null || con == null) {
            return false;
        }
        try {
            Statement state = con.createStatement();
            state.executeUpdate(statement);
        } catch (SQLException se) {
            System.out.println("\nSQL Exception occurred, the state : "
                    + se.getSQLState() + "\nMessage:\n" + se.getMessage() + "\n");
            this.errorMessage = se.getMessage();
            return false;
        }
        return true;
    }
    
    public void destroy() {
        this.username = null;
        this.password = null;
        this.instance = null;
    }
    
    public SearchListingsUI getPrevSearch() {
        if (comingFromUI) {
            return previousSearch;
        }
        return null;
    }
    
    public void setPrevSearch(SearchListingsUI searchUI) {
        this.previousSearch = searchUI;
    }
    
    public ReviewUI getPrevReview() {
        if (comingFromUI) {
            return previousReview;
        }
        return null;
    }
    
    public void setPrevReview(ReviewUI reviewUI) {
        this.previousReview = reviewUI;
    }
    
    public int getListingId() {
        return this.listingId;
    }
    
    public void setComingFromUI(boolean ui, int id) {
        this.comingFromUI = ui;
        this.listingId = id;
    }
    
    public String getErrorMessage() {
        return errorMessage;
    }
}
