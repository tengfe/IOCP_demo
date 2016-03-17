// CIOCPServer��Ĳ��Գ���

#include "CIocpServer.h"
#include <stdio.h>
#include <windows.h>

class CMyServer : public CIOCPServer
{
public:

	void OnConnectionEstablished(CIOCPContext *pContext, CIOCPBuffer *pBuffer)
	{
		printf("���յ�һ���µ�����(%d): %s\n",
			GetCurrentConnection(), ::inet_ntoa(pContext->addrRemote.sin_addr));
		printf("���ܵ�һ�����ݰ�, ���СΪ: %d�ֽ�\n", pBuffer->nLen);

		SendText(pContext, pBuffer->buff, pBuffer->nLen);
	}

	void OnConnectionClosing(CIOCPContext *pContext, CIOCPBuffer *pBuffer)
	{
		printf("һ�����ӹر�\n");
	}

	void OnConnectionError(CIOCPContext *pContext, CIOCPBuffer *pBuffer, int nError)
	{
		printf("һ�����ӷ�������: %d\n", nError);
	}

	void OnReadCompleted(CIOCPContext *pContext, CIOCPBuffer *pBuffer)
	{
		printf("���ܵ�һ�����ݰ�, ���СΪ: %d�ֽ�\n", pBuffer->nLen);
		SendText(pContext, pBuffer->buff, pBuffer->nLen);
	}

	void OnWriteCompleted(CIOCPContext *pContext, CIOCPBuffer *pBuffer)
	{
		printf("һ�����ݰ����ͳɹ�, ���СΪ: %d�ֽ�\n ", pBuffer->nLen);
	}
};

void main()
{
	CMyServer *pServer = new CMyServer;

	// ��������
	if (pServer->Start())
	{
		printf("�����������ɹ�...\n");
	}
	else
	{
		printf("����������ʧ��!\n");
		return;
	}

	// �����¼�������ServerShutdown�����ܹ��ر��Լ�
	HANDLE hEvent = ::CreateEvent(NULL, FALSE, FALSE, L"ShutdownEvent");
	::WaitForSingleObject(hEvent, INFINITE);
	::CloseHandle(hEvent);

	// �رշ���
	pServer->Shutdown();
	delete pServer;

	printf("�������ر�\n ");

}