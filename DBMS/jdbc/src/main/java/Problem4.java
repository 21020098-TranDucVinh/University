import java.sql.*;

public class Problem4 {
    public static void main(String[] args) throws SQLException {
        Connection conn = null;
        PreparedStatement stmt1 = null;
        PreparedStatement stmt2 = null;

        try {
            // Tạo kết nối đến cơ sở dữ liệu
            conn = Mysql.getConnection();

            // Bắt đầu giao dịch
            conn.setAutoCommit(false);

            // Thực hiện thao tác 1: thêm bản ghi vào bảng rental
            stmt1 = conn.prepareStatement("INSERT INTO rental (inventory_id, customer_id,staff_id) VALUES (?, ?, ?)");
            stmt1.setInt(1, 1);
            stmt1.setInt(2, 1);
            stmt1.setInt(3,-1);
            stmt1.executeUpdate();

            // Nếu thực hiện thành công, thực hiện commit giao dịch
            conn.commit();

            System.out.println("Giao dịch thành công!");

        } catch (SQLException e) {
            // Nếu xảy ra lỗi, thực hiện rollback giao dịch
            if (conn != null) {
                conn.rollback();
            }
            System.out.println("Giao dịch thất bại!");
            e.printStackTrace();
        } catch (Exception e) {
            throw new RuntimeException(e);
        } finally {
            // Đóng tất cả các kết nối và tài nguyên
            if (stmt1 != null) {
                stmt1.close();
            }
            if (stmt2 != null) {
                stmt2.close();
            }
            if (conn != null) {
                conn.close();
            }
        }
    }
}
