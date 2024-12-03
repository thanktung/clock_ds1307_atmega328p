1. Simulation: Proteus (8.13)
2. Code: Atmel Studio

Cách dùng hệ thống (3/12/2024):
1. Hệ thống có 3 mode tương ứng 3 case: 0=clock; 1=setup; 2=alarm
2. Chuyển case: GIỮ PB0 (nút trái) và ẤN PB1 (nút phải) để chuyển 
3. Ở case 0: ẤN PB1 (nút phải) để chuyển hiển thị ngày/giờ
4. Ở case 1: ẤN PB1 để chuyển các thành phần thiết lập theo thứ tự: giờ-phút-giây-ngày-tháng-năm-ngày trong tuần (hiển thị từng thành phần để thiết lập). ẤN PB0 để tăng giá trị thiết lập. Khi thiết lập xong 7 thành phần ấn tiếp PB1 sẽ lưu và trở về case0.
5. Ở case 2: ẤN PB1 để chuyển các thành phần thiết lập theo thự tự: giờ-phút (hiển thị từng thành phần để thiết lập). Khi thiết lập xong sẽ hiển thị cả giờ-phút, lúc này là đang đợi báo thức, khi đến lúc báo thức led sẽ nháy số 8 liên tục. ẤN PB1 để dừng lại hoặc ấn reset trên arduino để về ban đầu.
