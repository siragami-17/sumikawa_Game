//--------------------------------------------------------------------------------
//
//	�}�l�[�W������(���[�h) [manager.h]
//	Author:Yuna Sumikawa
//
//--------------------------------------------------------------------------------
#ifndef _MANAGER_H_
#define _MANAGER_H_

//-------------------------------------------------------------------------------
// �O���錾
//-------------------------------------------------------------------------------
class CRenderer;														// �����_�����O
class CInput_Keyboard;													// �L�[�{�[�h
class CSound;															// �T�E���h
class CGame;															// �Q�[���V�[��
class CTitle;															// �^�C�g��
class CTutorial;														// �`���[�g���A��
class CResult;															// ���U���g
class CFade;															// �t�F�[�h

//-------------------------------------------------------------------------------
// �}�l�[�W���N���X
//-------------------------------------------------------------------------------
class  CManager
{
public:

	// ���[�h�̎��
	typedef enum
	{
		MODE_TITLE = 0,		// �^�C�g��
		MODE_TUTORIAL,		// �`���[�g���A��
		MODE_GAME,			// �Q�[��
		MODE_RESULT,		// ���U���g
		MODE_MAX,
	}MODE;

	CManager();
	 ~CManager();

	 HRESULT Init(HWND hWnd, BOOL bWindow, HINSTANCE hInstance);						// ����������
	 void Uninit(void);																	// �I������
	 void Update(void);																	// �X�V����
	 void Draw(void);																	// �`�揈��

	 // ���[�h�֌W
	 static void CManager::SetMode(MODE mode);											// ���[�h�̐ݒ�@mode:���[�h�̎��
	 static MODE GetMode(void) { return m_mode; }										// �f�o�C�X�̎擾(���[�h)

	 // �f�o�C�X�̎擾
	 static CRenderer *GetRenderer(void) { return m_pRenderer; }						// �����_���[
	 static CInput_Keyboard *GetInputKeyboard(void) { return m_pInputKeyboard; }		// �L�[�{�[�h
	 static CSound *GetSound(void) { return m_pSound; }									// �T�E���h
	 static CFade *GetFade(void) { return m_pFade; }									// �t�F�[�h

	// �|�[�Y�֌W
	 static bool GetPause(void) { return m_bPause; }
	 static void SetPause(bool bPause);
	 static void SetPause(void);

private:
	// ���[�h�֌W
	static CTitle *m_pTitle;											// �^�C�g��
	static CTutorial *m_pTutoral;										// �`���[�g���A��
	static CGame *m_pGame;												// �Q�[��
	static CResult * m_pResult;											// ���U���g
	static MODE m_mode;													// ���[�h

	static CRenderer *m_pRenderer;										// �����_�����O�̃|�C���^
	static CInput_Keyboard *m_pInputKeyboard;							// �L�[�{�[�h�̃|�C���^
	static CSound *m_pSound;											// �T�E���h�̃|�C���^
	static CFade *m_pFade;												// �t�F�[�h�̃|�C���^

	static bool m_bPause;												// �|�[�Y�����ǂ���
};

#endif