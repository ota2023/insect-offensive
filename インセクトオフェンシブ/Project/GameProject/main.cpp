#include "TaskManager.h"
#include "Player.h"
#include "Slime.h"
#include "Catp.h"
#include "Bee.h"
#include "EnemyManager.h"

//--------------------------------------------
//�O���[�o���ϐ��̈�
//--------------------------------------------
Player* g_player = nullptr;	// �v���C���[�̃|�C���^
Slime* g_slime = nullptr;	// �X���C���̃|�C���^
Catp* g_catp = nullptr;		//�@�P���V�̃|�C���^
Bee* g_bee = nullptr;		//�@�n�`�̃|�C���^

CImage* g_field = nullptr;	// �t�B�[���h�摜�̃|�C���^


void MainLoop()
{
	//--------------------------------------------------------------
	//�Q�[�����̓����͂����ɏ���
	//�Q�[�����͂��̊֐�_��1�b�Ԃ�60��Ăяo���Ă���
	//--------------------------------------------------------------

	//�S�^�X�N���X�V
	TaskManager::Instance()->Update();

	// �t�B�[���h�摜��`��
	g_field->Draw();	//�t�B�[���h���^�X�N�Ǘ����悤�i�^�X�N�ɂ��āj

	//�S�Ẵ^�X�N��`��
	TaskManager::Instance()->Render();

	// �f�o�b�O�����̕`��
	DebugPrint::Render();	//�{���̓^�X�N��

	//��͓����蔻��̎��s�Ƃ��ɂȂ邩��

}
void Init()
{
	CFPS::SetFPS(60);
	//�t���[�����䏉����
	CFPS::Init();
	//�{�^���̐ݒ�
	CInput::Init();
	CInput::SetButton(0, CInput::eButton1, 'Z');
	CInput::SetButton(0, CInput::eButton2, 'J');
	CInput::SetButton(0, CInput::eButton3, 'C');
	CInput::SetButton(0, CInput::eButton4, 'V');
	CInput::SetButton(0, CInput::eButton5, VK_SPACE);
	CInput::SetButton(0, CInput::eButton10, VK_RETURN);
	CInput::SetButton(0, CInput::eUp, 'W');
	CInput::SetButton(0, CInput::eDown, 'S');
	CInput::SetButton(0, CInput::eLeft, 'A');
	CInput::SetButton(0, CInput::eRight, 'D');
	CInput::SetButton(0, CInput::eMouseL, VK_LBUTTON);
	CInput::SetButton(0, CInput::eMouseR, VK_RBUTTON);
	CInput::SetButton(0, CInput::eMouseC, VK_MBUTTON);
	//	CInput::SetMouseInside(true);
	//	CInput::ShowCursor(false);
	CInput::Update();
	CInput::Update();

	SetCurrentDirectory("data");
	CSound::GetInstance();

	//-----------------------------------------------------
	//�������̖��߂�����
	//�Q�[���N�����Ɉ�x�����Ă΂��
	//-----------------------------------------------------

	// �t�B�[���h�̉摜�𐶐�
	g_field = CImage::CreateImage("�w�i�܂Ƃ�.png");


	// �v���C���[�𐶐�
	g_player = new Player(
		CVector3D(SCREEN_WIDTH * 0.5f, 0.0f, 0.0f));

	// �X���C���𐶐�
	//g_slime = new Slime(0,
		//CVector3D(SCREEN_WIDTH * 0.75f,0.0f, 0.0f));

	//�@�P���V�𐶐�
	g_catp = new Catp(0,
		CVector3D(SCREEN_WIDTH * 1.3f, 0.0f, 0.0f));
	//�@�P���V�𐶐�
	g_catp = new Catp(0,
		CVector3D(SCREEN_WIDTH * 1.7f, 0.0f, -200.0f));
	//�@�P���V�𐶐�
	g_catp = new Catp(0,
		CVector3D(SCREEN_WIDTH * 1.9f, 0.0f,150.0f));
	//�@�P���V�𐶐�
	g_catp = new Catp(0,
		CVector3D(SCREEN_WIDTH * 2.2f, 0.0f, 50.0f));
	//�@�P���V�𐶐�
	g_catp = new Catp(0,
		CVector3D(SCREEN_WIDTH * 2.4f, 0.0f, -200.0f));
	//�@�P���V�𐶐�
	g_catp = new Catp(0,
		CVector3D(SCREEN_WIDTH * 2.4f, 0.0f, 0.0f));
	//�@�P���V�𐶐�
	g_catp = new Catp(0,
		CVector3D(SCREEN_WIDTH * 2.4f, 0.0f, 150.0f));

	//�@�n�`�𐶐�
	g_bee = new Bee(0,
		CVector3D(SCREEN_WIDTH * 1.3f, 250.0f, -100.0f));
	//�@�n�`�𐶐�
	g_bee = new Bee(0,
		CVector3D(SCREEN_WIDTH * 2.0f, 50.0f, -100.0f));
	//�@�n�`�𐶐�
	g_bee = new Bee(0,
		CVector3D(SCREEN_WIDTH * 2.5f, 50.0f, -100.0f));
	//�@�n�`�𐶐�
	g_bee = new Bee(0,
		CVector3D(SCREEN_WIDTH * 2.8f, 250.0f, -100.0f));
	//�@�n�`�𐶐�
	g_bee = new Bee(0,
		CVector3D(SCREEN_WIDTH * 3.5f, 50.0f, -100.0f));
	//�@�n�`�𐶐�
	g_bee = new Bee(0,
		CVector3D(SCREEN_WIDTH * 4.0f, 50.0f, -100.0f));


}


void Release()
{
	DebugPrint::ClearInstance();
	CLoadThread::ClearInstance();
	CSound::ClearInstance();
	CResourceManager::ClearInstance();
	TaskManager::ClearInstance();
}

static void ResizeCallback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);

	//��ʉ𑜓x�ϓ�
	CCamera::GetCamera()->SetSize((float)w, (float)h);
	//��ʉ𑜓x�Œ�
	//CCamera::GetCamera()->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	CCamera::GetCamera()->Viewport(0, 0, w, h);
	CCamera::GetCurrent()->Perspective(DtoR(60.0), (float)w / (float)h, 1.0, 1000.0);

	glfwGetWindowPos(window, &GL::window_x, &GL::window_y);
	GL::UpdateWindowRect(GL::window_x, GL::window_y, w, h);
	CInput::UpdateClipCursor(true);

}
static void WheelCallback(GLFWwindow* _window, double _offsetx, double _offsety)
{
	CInput::AddMouseWheel((int)_offsety);
}
static void PosCallback(GLFWwindow* _window, int x, int y)
{
	GL::window_x = x;
	GL::window_y = y;
	GL::UpdateWindosRect(x, y, GL::window_width, GL::window_height);
	CInput::UpdateClipCursor(true);
}
static void FocusCallback(GLFWwindow* _window, int f)
{
	CInput::UpdateClipCursor(f);
	GL::focus = f;
}

static void error_callback(int error, const char* description)
{
	printf("Error: %s\n", description);
}

//�t���X�N���[��?�E�C���h�E���[�h�̐؂�ւ�
//Alt+Enter�Ő؂�ւ���
void CheckFullScreen()
{
	static int key_enter = 0;
	int key_enter_buf = key_enter;
	if (key_enter_buf ^ (key_enter = glfwGetKey(GL::window, GLFW_KEY_ENTER)) && key_enter && (glfwGetKey(GL::window, GLFW_KEY_LEFT_ALT) || glfwGetKey(GL::window, GLFW_KEY_RIGHT_ALT)))
	{
		GL::ChangeFullScreen(!GL::full_screen);
	}
}

int __main(int* argcp, char** argv)
{
	// ���������[�N���o
	//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	//OpenGL4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) return -1;
	//	glutInit(argcp, argv);

	GL::window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Simple", nullptr, nullptr);
	glfwGetWindowSize(GL::window, &GL::window_width, &GL::window_height);
	glfwGetWindowPos(GL::window, &GL::window_x, &GL::window_y);

	glfwSetFramebufferSizeCallback(GL::window, ResizeCallback);
	glfwSetScrollCallback(GL::window, WheelCallback);
	glfwSetWindowFocusCallback(GL::window, FocusCallback);
	glfwSetWindowPosCallback(GL::window, PosCallback);
	if (!GL::window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(GL::window);
	glfwSwapInterval(1);
	ResizeCallback(GL::window, SCREEN_WIDTH, SCREEN_HEIGHT);

	GLenum err = glewInit();
	if (err == GLEW_OK)
	{
		printf("%s\n", glewGetString(GLEW_VERSION));
	}
	else
	{
		printf("%s\n", glewGetErrorString(err));
		getchar();
		return -1;
	}
	HDC glDc = wglGetCurrentDC();
	GL::hWnd = WindowFromDC(glDc);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);//�u�����h�̗L����
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//�Œ�V�F�[�_�[�p
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_ALPHA_TEST);

	Init();
	while (!glfwWindowShouldClose(GL::window))
	{
		CheckFullScreen();


		CInput::Update();
		//�e�o�b�t�@�[���N���A
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		MainLoop();


		glfwSwapBuffers(GL::window);


		CFPS::Wait();

		char title[32];
		sprintf_s(title, "Sample3");
		glfwSetWindowTitle(GL::window, title);

		glfwPollEvents();
		if (glfwGetKey(GL::window, GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(GL::window, GL_TRUE);
		}

	}

	glfwTerminate();

	Release();
	return 0;
}

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR argv, INT argc)
{
	return __main(&__argc, __argv);
}

int main(int argc, char** argv)
{
	return __main(&argc, argv);
}