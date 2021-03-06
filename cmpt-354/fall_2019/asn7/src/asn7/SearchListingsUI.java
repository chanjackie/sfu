/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package asn7;

import java.sql.*;
import java.util.ArrayList;
import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumn;

/**
 *
 * @author jgc11
 */
public class SearchListingsUI extends JFrame {
    private ConSingleton con;
    private int selectedListingId;

    /**
     * Creates new form SearchListingsUI
     */
    public SearchListingsUI() {
        initComponents();
        con = ConSingleton.getInstance();
        TableColumn column = null;
        for (int i=0; i<5; i++) {
            column = searchResultsTable.getColumnModel().getColumn(i);
            if (i == 0) {
                column.setPreferredWidth(150);
            } else if (i == 1) {
                column.setPreferredWidth(350);                
            } else if (i == 2) {
                column.setPreferredWidth(250);                
            } else if (i == 3) {
                column.setPreferredWidth(100);                
            } else if (i == 4) {
                column.setPreferredWidth(140);                
            }
        }
        searchBookBtn.setVisible(false);
        searchResultsTable.getSelectionModel().addListSelectionListener(new ListSelectionListener() {
            @Override
            public void valueChanged(ListSelectionEvent e) {
                if (searchResultsTable.getModel().getRowCount() == 0) {
                    searchBookBtn.setVisible(false);
                    return;
                }
                System.out.println(searchResultsTable.getValueAt(searchResultsTable.getSelectedRow(), 0).toString());
                if (!searchResultsTable.getValueAt(searchResultsTable.getSelectedRow(), 0).toString().contains("No")) {
                    selectedListingId = Integer.valueOf(searchResultsTable.getValueAt(searchResultsTable.getSelectedRow(), 0).toString());        
                    searchBookBtn.setVisible(true);            
                } else {
                    searchBookBtn.setVisible(false);
                }
            }
            
        });
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jPanel1 = new javax.swing.JPanel();
        jLabel1 = new javax.swing.JLabel();
        jLabel2 = new javax.swing.JLabel();
        jLabel3 = new javax.swing.JLabel();
        jLabel4 = new javax.swing.JLabel();
        jLabel5 = new javax.swing.JLabel();
        searchSearchBtn = new javax.swing.JButton();
        jButton1 = new javax.swing.JButton();
        searchStartDate = new javax.swing.JFormattedTextField();
        searchEndDate = new javax.swing.JFormattedTextField();
        searchNumBeds = new javax.swing.JFormattedTextField();
        searchMinPrice = new javax.swing.JFormattedTextField();
        searchMaxPrice = new javax.swing.JFormattedTextField();
        jScrollPane6 = new javax.swing.JScrollPane();
        searchResultsTable = new javax.swing.JTable();
        searchBookBtn = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setResizable(false);

        jPanel1.setBorder(javax.swing.BorderFactory.createTitledBorder("Search Listings"));

        jLabel1.setText("Max Price:");

        jLabel2.setText("Min Price:");

        jLabel3.setText("Start Date (yyyy-MM-dd):");

        jLabel4.setText("End Date (yyyy-MM-dd):");

        jLabel5.setText("Num. Bedrooms:");

        searchSearchBtn.setText("Search");
        searchSearchBtn.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                searchSearchBtnActionPerformed(evt);
            }
        });

        jButton1.setText("Back");
        jButton1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton1ActionPerformed(evt);
            }
        });

        searchStartDate.setFormatterFactory(new javax.swing.text.DefaultFormatterFactory(new javax.swing.text.DateFormatter(new java.text.SimpleDateFormat("yyyy-MM-dd"))));
        searchStartDate.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                searchStartDateActionPerformed(evt);
            }
        });

        searchEndDate.setFormatterFactory(new javax.swing.text.DefaultFormatterFactory(new javax.swing.text.DateFormatter(new java.text.SimpleDateFormat("yyyy-MM-dd"))));

        searchNumBeds.setFormatterFactory(new javax.swing.text.DefaultFormatterFactory(new javax.swing.text.NumberFormatter(new java.text.DecimalFormat("#0"))));
        searchNumBeds.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                searchNumBedsActionPerformed(evt);
            }
        });

        searchMinPrice.setFormatterFactory(new javax.swing.text.DefaultFormatterFactory(new javax.swing.text.NumberFormatter(new java.text.DecimalFormat("#,##0.##"))));
        searchMinPrice.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                searchMinPriceActionPerformed(evt);
            }
        });

        searchMaxPrice.setFormatterFactory(new javax.swing.text.DefaultFormatterFactory(new javax.swing.text.NumberFormatter(new java.text.DecimalFormat("#,##0.##"))));
        searchMaxPrice.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                searchMaxPriceActionPerformed(evt);
            }
        });

        searchResultsTable.setFont(new java.awt.Font("Calibri Light", 0, 18)); // NOI18N
        searchResultsTable.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {

            },
            new String [] {
                "ID", "Name", "Description", "# Beds", "Price"
            }
        ) {
            boolean[] canEdit = new boolean [] {
                false, false, false, false, false
            };

            public boolean isCellEditable(int rowIndex, int columnIndex) {
                return canEdit [columnIndex];
            }
        });
        searchResultsTable.setSelectionMode(javax.swing.ListSelectionModel.SINGLE_SELECTION);
        jScrollPane6.setViewportView(searchResultsTable);

        searchBookBtn.setText("Book");
        searchBookBtn.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                searchBookBtnActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanel1Layout.createSequentialGroup()
                        .addGap(6, 6, 6)
                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                            .addGroup(jPanel1Layout.createSequentialGroup()
                                .addComponent(jLabel2)
                                .addGap(18, 18, 18)
                                .addComponent(searchMinPrice, javax.swing.GroupLayout.PREFERRED_SIZE, 140, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addGroup(jPanel1Layout.createSequentialGroup()
                                .addComponent(jLabel1)
                                .addGap(18, 18, 18)
                                .addComponent(searchMaxPrice, javax.swing.GroupLayout.PREFERRED_SIZE, 140, javax.swing.GroupLayout.PREFERRED_SIZE)))
                        .addGap(18, 18, 18)
                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                            .addGroup(jPanel1Layout.createSequentialGroup()
                                .addComponent(jLabel4)
                                .addGap(18, 18, 18)
                                .addComponent(searchEndDate, javax.swing.GroupLayout.PREFERRED_SIZE, 140, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addGroup(jPanel1Layout.createSequentialGroup()
                                .addComponent(jLabel3)
                                .addGap(18, 18, 18)
                                .addComponent(searchStartDate, javax.swing.GroupLayout.PREFERRED_SIZE, 140, javax.swing.GroupLayout.PREFERRED_SIZE)))
                        .addGap(18, 18, 18)
                        .addComponent(jLabel5)
                        .addGap(18, 18, 18)
                        .addComponent(searchNumBeds, javax.swing.GroupLayout.PREFERRED_SIZE, 74, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 15, Short.MAX_VALUE)
                        .addComponent(searchBookBtn, javax.swing.GroupLayout.PREFERRED_SIZE, 80, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(searchSearchBtn, javax.swing.GroupLayout.PREFERRED_SIZE, 77, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jButton1, javax.swing.GroupLayout.PREFERRED_SIZE, 65, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addComponent(jScrollPane6))
                .addContainerGap())
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jScrollPane6, javax.swing.GroupLayout.DEFAULT_SIZE, 467, Short.MAX_VALUE)
                .addGap(18, 18, 18)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanel1Layout.createSequentialGroup()
                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                .addComponent(jLabel3)
                                .addComponent(searchStartDate, javax.swing.GroupLayout.PREFERRED_SIZE, 24, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addGroup(jPanel1Layout.createSequentialGroup()
                                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                    .addComponent(jLabel1)
                                    .addComponent(searchMaxPrice, javax.swing.GroupLayout.PREFERRED_SIZE, 24, javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addGap(12, 12, 12)
                                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                        .addComponent(jLabel4)
                                        .addComponent(searchEndDate, javax.swing.GroupLayout.PREFERRED_SIZE, 24, javax.swing.GroupLayout.PREFERRED_SIZE))
                                    .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                        .addComponent(jLabel2)
                                        .addComponent(searchMinPrice, javax.swing.GroupLayout.PREFERRED_SIZE, 24, javax.swing.GroupLayout.PREFERRED_SIZE)))))
                        .addGap(8, 8, 8))
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, jPanel1Layout.createSequentialGroup()
                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                .addComponent(searchSearchBtn, javax.swing.GroupLayout.PREFERRED_SIZE, 44, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addComponent(jButton1, javax.swing.GroupLayout.PREFERRED_SIZE, 44, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addComponent(searchBookBtn, javax.swing.GroupLayout.PREFERRED_SIZE, 44, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                .addComponent(jLabel5)
                                .addComponent(searchNumBeds, javax.swing.GroupLayout.PREFERRED_SIZE, 24, javax.swing.GroupLayout.PREFERRED_SIZE)))
                        .addGap(16, 16, 16))))
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jPanel1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jPanel1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void jButton1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton1ActionPerformed
        // TODO add your handling code here:
        con.setComingFromUI(false, 0);
        con.setPrevSearch(null);
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new MainMenu().setVisible(true);
            }
        });
        this.dispose();
    }//GEN-LAST:event_jButton1ActionPerformed

    private void searchStartDateActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_searchStartDateActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_searchStartDateActionPerformed

    private void searchSearchBtnActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_searchSearchBtnActionPerformed
        // TODO add your handling code here:
        String query = buildQuery();
        ResultSet rs = con.query(query);
        ArrayList<String[]> dataList = new ArrayList<>();
        
        try {
            while (rs.next()) {
                String[] dataRow = new String[5];
                dataRow[0] = rs.getString("id");
                dataRow[1] = rs.getString("name");
                String desc = rs.getString("description");
                if (desc.length() <= 25) {
                    dataRow[2] = desc;
                } else {
                    dataRow[2] = desc.substring(0, 25);
                }
                dataRow[3] = rs.getString("number_of_bedrooms");
                dataRow[4] = rs.getString("price");
                dataList.add(dataRow);
            }
            rs.close();            
        } catch (SQLException se) {
            System.out.println("\nSQL Exception occurred, the state : "
                    + se.getSQLState() + "\nMessage:\n" + se.getMessage() + "\n");
            return;
        }
        DefaultTableModel model = (DefaultTableModel) searchResultsTable.getModel();
        model.setRowCount(0);
        for (int i=0; i<dataList.size(); i++) {
            model.addRow(dataList.get(i));
        }
        if (dataList.isEmpty()) {
            String[] empty = new String[5];
            empty[0] = "No results found";
            model.addRow(empty);
        }
    }//GEN-LAST:event_searchSearchBtnActionPerformed

    private String buildQuery() {
        String startDate = searchStartDate.getText();
        if (startDate.isEmpty()) {
            startDate = "1000-01-01";
        }
        String endDate = searchEndDate.getText();
        if (endDate.isEmpty()) {
            endDate = "9999-01-01";
        }
        String numBeds = searchNumBeds.getText();
        if (numBeds.isEmpty()) {
            numBeds = "0";
        }
        String maxPrice = searchMaxPrice.getText();
        if (maxPrice.isEmpty()) {
            maxPrice = "99999999";
        }
        String minPrice = searchMinPrice.getText();
        if (minPrice.isEmpty()) {
            minPrice = "0";
        }
        String query = "SELECT L.id, L.name, L.description, L.number_of_bedrooms, MAX(C.price) AS price" + "\n"
            + "FROM listings L JOIN calendar C ON C.listing_id = L.id" + "\n"
            + "WHERE C.date <= '" + endDate + "' AND C.date >= '" + startDate + "' \n"
            + "AND C.available = 1 AND L.number_of_bedrooms >= " + numBeds + "\n"
            + "GROUP BY L.id, L.name, L.description, L.number_of_bedrooms" + "\n"
            + "HAVING MAX(C.price) <= " + maxPrice + " AND MAX(C.price) >= " + minPrice + ";";
        System.out.println(query);
        return query;
    }
    
    private void searchNumBedsActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_searchNumBedsActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_searchNumBedsActionPerformed

    private void searchMinPriceActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_searchMinPriceActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_searchMinPriceActionPerformed

    private void searchMaxPriceActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_searchMaxPriceActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_searchMaxPriceActionPerformed

    private void searchBookBtnActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_searchBookBtnActionPerformed
        // TODO add your handling code here:
        con.setPrevSearch(this);
        con.setComingFromUI(true, selectedListingId);
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new BookListingsUI().setVisible(true);
            }
        });
        this.setVisible(false);
    }//GEN-LAST:event_searchBookBtnActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (UIManager.LookAndFeelInfo info : UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(SearchListingsUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(SearchListingsUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(SearchListingsUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(SearchListingsUI.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new SearchListingsUI().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton jButton1;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JScrollPane jScrollPane6;
    private javax.swing.JButton searchBookBtn;
    private javax.swing.JFormattedTextField searchEndDate;
    private javax.swing.JFormattedTextField searchMaxPrice;
    private javax.swing.JFormattedTextField searchMinPrice;
    private javax.swing.JFormattedTextField searchNumBeds;
    private javax.swing.JTable searchResultsTable;
    private javax.swing.JButton searchSearchBtn;
    private javax.swing.JFormattedTextField searchStartDate;
    // End of variables declaration//GEN-END:variables

}
