import java.sql.*;

public class Mysql {
    private static String DB_URL = "jdbc:mysql://localhost:3306/sakila";
    private static String USER_NAME = "root";
    private static String PASSWORD = "";
    public static Connection getConnection() throws Exception {
        Class.forName("com.mysql.cj.jdbc.Driver");
        Connection conn = DriverManager.getConnection(DB_URL, USER_NAME, PASSWORD);
        System.out.println("connect successfully!");
        return conn;
    }

    public static String getQuery(String query,Connection conn) {
        StringBuilder result = new StringBuilder();
        try {
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery(query);

            while (rs.next()) {
                result.append(rs.getString(1)).append("\n");
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
        return result.toString();
    }
}