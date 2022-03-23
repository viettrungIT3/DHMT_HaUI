//Chương trình vẽ 1 tam giác theo mô hình lập trình OpenGL hiện đại

#include "Angel.h"  /* Angel.h là file tự phát triển (tác giả Prof. Angel), có chứa cả khai báo includes glew và freeglut*/

using namespace std;

// Cấu trúc các hàm trong file
void generateGeometry( void );
void initGPUBuffers( void );
void shaderSetup( void );
void display( void );
void keyboard( unsigned char key, int x, int y );

GLuint program;

typedef vec2 point2;
// Số các đỉnh của tập các đoạn thẳng
const int NumPoints = 24;

// Mảng các đỉnh của hình cần vẽ
point2 points[NumPoints];

void generateGeometry( void )
{
	//// Chỉ rõ các đỉnh cho một tam giác
	//points[0] = point2( -0.5, -0.5 );
	//points[1] = point2( 0.0, 0.5 );
	//points[2] = point2( 0.5, -0.5 );

    //// Hình chữ nhật được cấu tạo từ tam giác 1 và tam giác 2
    //// Chỉ rõ các đỉnh cho một tam giác 1
    //points[0] = point2(-0.5, -0.5);
    //points[1] = point2(0.5, 0.5);
    //points[2] = point2(-0.5, 0.5);

    //// Chỉ rõ các đỉnh cho một tam giác 2
    //points[3] = point2(-0.5, -0.5);
    //points[4] = point2(0.5, 0.5);
    //points[5] = point2(0.5, -0.5);
	
    // Hình quạt
    int index = 0;
    points[index++] = point2(-0.433, 0.24);
    points[index++] = point2(-0.353, 0.364);
    points[index++] = point2(0, 0);

    points[index++] = point2(-0.353, 0.354);
    points[index++] = point2(-0.25, 0.443);
    points[index++] = point2(0, 0);

    points[index++] = point2(-0.25, 0.433);
    points[index++] = point2(-0.129, 0.493);
    points[index++] = point2(0, 0);

    points[index++] = point2(-0.129, 0.483);
    points[index++] = point2(0, 0.52);
    points[index++] = point2(0, 0);

    points[index++] = point2(0, 0.52);
    points[index++] = point2(0.129, 0.483);
    points[index++] = point2(0, 0);

    
    points[index++] = point2(0.129, 0.493);
    points[index++] = point2(0.25, 0.433);
    points[index++] = point2(0, 0);

    points[index++] = point2(0.25, 0.443);
    points[index++] = point2(0.353, 0.354);
    points[index++] = point2(0, 0);

    points[index++] = point2(0.353, 0.364);
    points[index++] = point2(0.433, 0.24);
    points[index++] = point2(0, 0);

    /*int index = 0, x1 = 0, y1 = 0.5, x2, y2;
    for (int i = 0; i < 3; i++)
    {
        points[index++] = point2(x1, y1);
        x2 = x1 * cos(M_PI / 12) - y1 * sin(M_PI / 12);
        y2 = sqrt(0.25 - x2 * x2);
        points[index++] = point2(x2, y2);
        points[index++] = point2(0, 0);
        x1 = x2;
        y1 = y2;
    }*/
	
}


void initGPUBuffers( void )
{
	// Tạo một VAO - vertex array object
	GLuint vao;
    glGenVertexArrays( 1, &vao );     
    glBindVertexArray( vao );

    // Tạo và khởi tạo một buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW );
}


void shaderSetup( void )
{
	// Nạp các shader và sử dụng chương trình shader
    program = InitShader( "vshader1.glsl", "fshader1.glsl" );   // hàm InitShader khai báo trong Angel.h
    glUseProgram( program );

    // Khởi tạo thuộc tính vị trí đỉnh từ vertex shader
    GLuint loc = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

    glClearColor( 1.0, 1.0, 1.0, 1.0 );        /* Thiết lập màu trắng là màu xóa màn hình*/
}


void display( void )
{
	// All drawing happens in display function
    glClear( GL_COLOR_BUFFER_BIT );                /* Xóa bộ đệm màu màn hình bằng màu thiết lập bởi glClearColor() - Xóa màn hình*/
    //glDrawArrays( GL_LINE_LOOP, 0, NumPoints );    /*Vẽ các đoạn thẳng*/
    glDrawArrays(GL_TRIANGLES, 0, NumPoints );    /*Tô đậm nền*/
    glFlush();									   /* Đẩy việc thực thi các lệnh OpenGL đến phần cứng đồ họa - thực thi lệnh OpenGL trong thời gian hữu hạn*/
}


void keyboard( unsigned char key, int x, int y )
{
	// keyboard handler

    switch ( key ) {
    case 033:			// 033 is Escape key octal value
        exit(1);		// quit program
        break;
    }
}


int main( int argc, char **argv )
{
	// main function: program starts here

    glutInit( &argc, argv );                         
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB ); 
    glutInitWindowSize( 640, 480 );                 
	glutInitWindowPosition(100,150);              
    glutCreateWindow( "Starting App" );           

   
	glewInit();										// Khởi tạo glew

    generateGeometry( );                           // Gọi hàm sinh các điểm để vẽ 
    initGPUBuffers( );							   // Tạo GPU buffers
    shaderSetup( );                                // Kết nối file .cpp này với file shader

    glutDisplayFunc( display );                    // Đăng ký hàm gọi lại về hiển thị
    glutKeyboardFunc( keyboard );                  // Đăng ký hàm gọi lại cho sự kiện bàn phím

	// Có thể thêm các hàm gọi lại về điều khiển chuột, thay đổi kích cỡ cửa sổ, ... ở đây

	// Đưa vào vòng lặp vô hạn
    glutMainLoop();
    return 0;
}
