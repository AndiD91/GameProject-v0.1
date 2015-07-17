#pragma once
#include <DirectXTemplatePCH.h>
#include "Vertex.h"
#include <vector>
#include <map>
#include "Camera.h"

class Engine
{
public:
	Engine();
	~Engine();
	
enum Rendertype
{
	OPENGL,
	DIRECTX,
};
const BOOL initEngine(HINSTANCE& hInstance, HWND hwnd,const Rendertype rendertype);
void Cleanup();
void Clear(const FLOAT clearColor[4], const FLOAT clearDepth, const UINT8 clearStencil);
void Update(const FLOAT deltaTime);
void Render();
void setVSync(const BOOL value);

void setActiveCamera(Camera& camera);

private:
	


	Camera* m_camera;


	HWND g_WindowHandle = nullptr;
	BOOL g_EnableVSync = FALSE;

	// Direct3D device and swap chain.
	ID3D11Device* g_d3dDevice = nullptr;
	ID3D11DeviceContext* g_d3dDeviceContext = nullptr;
	IDXGISwapChain* g_d3dSwapChain = nullptr;

	// Render target view for the back buffer of the swap chain.
	ID3D11RenderTargetView* g_d3dRenderTargetView = nullptr;
	// Depth/stencil view for use as a depth buffer.
	ID3D11DepthStencilView* g_d3dDepthStencilView = nullptr;
	// A texture to associate to the depth stencil view.
	ID3D11Texture2D* g_d3dDepthStencilBuffer = nullptr;

	// Define the functionality of the depth/stencil stages.
	ID3D11DepthStencilState* g_d3dDepthStencilState = nullptr;
	// Define the functionality of the rasterizer stage.
	ID3D11RasterizerState* g_d3dRasterizerState = nullptr;
	D3D11_VIEWPORT g_Viewport;

	// Vertex buffer data
	ID3D11InputLayout* g_d3dInputLayout = nullptr;
	ID3D11Buffer* g_d3dVertexBuffer = nullptr;
	ID3D11Buffer* g_d3dIndexBuffer = nullptr;

	// Shader data
	ID3D11VertexShader* g_d3dVertexShader = nullptr;
	ID3D11PixelShader* g_d3dPixelShader = nullptr;

	// Shader resources
	enum ConstanBuffer
	{
		CB_Appliation,
		CB_Frame,
		CB_Object,
		NumConstantBuffers
	};//kommentar

	ID3D11Buffer* g_d3dConstantBuffers[NumConstantBuffers];

	// Demo parameters
	DirectX::XMMATRIX g_WorldMatrix;
	//DirectX::XMMATRIX g_ViewMatrix;
	DirectX::XMMATRIX g_ProjectionMatrix;

	// Vertex data for a colored cube.
	struct VertexPosColor
	{
		DirectX::XMFLOAT3 Position;
		DirectX::XMFLOAT3 Color;

		VertexPosColor(DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 color)
		{
			Position = position;
			Color = color;
		}
	};

	std::vector<Vertex> g_Vertices;
	std::vector<WORD> g_Indicies;


	const DXGI_RATIONAL& QueryRefreshRate(const UINT screenWidth, const UINT screenHeight, const BOOL vsync);

	const INT InitDirectX(const HINSTANCE hInstance, const BOOL vSync);


	const BOOL LoadContent();


	// Get the latest profile for the specified shader type.
	
	const std::string& GetLatestVertexProfile();
	const std::string& GetLatestPixelProfile();


	
	ID3D11VertexShader* CreateVertexShader(ID3DBlob* pShaderBlob, ID3D11ClassLinkage* pClassLinkage);
	ID3D11PixelShader* CreatePixelShader(ID3DBlob* pShaderBlob, ID3D11ClassLinkage* pClassLinkage);


	template< class ShaderClass >
	ShaderClass* LoadShader(const std::wstring& fileName, const std::string& entryPoINT, const std::string& _profile);

	

	//Release Com Objects
	void UnloadContent();

	
	void showFPS(const FLOAT deltaTime);

	void Present(const BOOL vSync);
	
};