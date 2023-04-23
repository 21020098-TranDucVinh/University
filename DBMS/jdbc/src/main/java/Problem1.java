import java.sql.*;

public class Problem1 {

    public static void main(String... args) {
        try {
            Connection conn = Mysql.getConnection();

            String sql = """
                    SELECT f.*
                    FROM film_actor fa
                    JOIN film f ON f.film_id = fa.film_id
                    WHERE fa.actor_id = 1;""";

            // crate statement
            Statement stmt = conn.createStatement();

            // select 'actor'
            ResultSet rs = stmt.executeQuery(sql);

            ResultSetMetaData title = rs.getMetaData();
            int columnCount = title.getColumnCount();

            // Iterate over the columns
            for (int i = 1; i < 5; i++) {
                String columnName = title.getColumnName(i);
                System.out.printf(columnName + "\t");
            }
            System.out.println();

            // show data
            while (rs.next()) {
                System.out.println(rs.getInt(1)
                        + "\t" + rs.getString(2)
                        + "\t" + rs.getString(3)
                        + "\t" + rs.getInt(4));
            }

            // close connection
            conn.close();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}
