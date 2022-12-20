#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

#include <nlohmann/json.hpp>

#include "include/Hash.hpp"
#include "include/Block.hpp"
#include "common.hpp"
#include "include/BlockChain.hpp"
#include "net/requests.hpp"

using json = nlohmann::json;

#include "net/client_http.hpp"
#include "net/server_http.hpp"

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;

/*
 * Main function - sets up server, command line interface
 */

using namespace std;

// int main()
// {
//     // printf("Welcome! To quit-> Control c \n");
//     // HttpServer server;

//     // // Set up ports

//     // int port{};
//     // printf("Enter port: ");
//     // scanf("%d",&port);
//     // server.config.port = port; //server port

//     // std::vector<int> listOfNodes; //vector of the ports of nodes in the network

//     // // BLOCK CHAIN INITIALIZATION AND ADDING SELF TO NETWORK

//     // char ch;
//     // printf("Are you the initial Node? (y or n) ");
//     // scanf(" %c",&ch);
//     // BlockChain bc;

//     // if (ch == 'y'){
//     //     // Initial Node: setup Blockchain with genesis block
//     //     bc = BlockChain(0);
//     // }
//     // else if(ch =='n'){
//     //     // New Node - need to add self to network by providing ports
//     //     bc = BlockChain(0);
//     //     char otherPorts[50];
//     //     // Example input: 8000,3000,3030
//     //     printf("Enter ports of nodes in network(with commas in between): ");
//     //     scanf("%s",otherPorts);
//     //     std::stringstream ss(otherPorts);
//     //     int i{};
//     //     // parse string of nodes and add them to listOfNoes
//     //     while (ss >> i){
//     //         listOfNodes.push_back(i);
//     //         if (ss.peek() == ',' || ss.peek() == ' ')
//     //             ss.ignore();
//     //     }

//     //     addSelfToNetwork(&listOfNodes,server.config.port);
//     //     json chain = getChainFromNodes(&listOfNodes);
//     //     //skips first block - same genesis block across all nodes
//     //     for (int a = 1; a <chain["length"].get<int>(); a++ ){
//     //         auto block = chain["data"][a];
//     //         std::vector<std::string> data = block["data"].get<std::vector<std::string> >();
//     //         bc.addBlock(block["index"],block["previousHash"],block["hash"],block["nonce"],data);
//     //     }
//     // }
//     // else {
//     //     return 0;
//     // }

//     // // SERVER INITIALIZATION

//     // /* POST /addnode - used to add node to network, called by new node to all the nodes in the network
//     //  * adds node(port) to listOfNodes
//     // */
//     // server.resource["^/addnode$"]["POST"] = [&listOfNodes](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
//     //     printf("POST /addnode --- New Node adding to network....\n");
//     //     try {
//     //         json content = json::parse(request->content);
//     //         int port = content["port"].get<int>();
//     //         listOfNodes.push_back(port); // Adds port to listOfNodes
//     //         printf("----Adding node %d to listOfNodes\n",port);
//     //         response->write("Added You to our List");
//     //     }
//     //     catch(const exception &e) {
//     //         *response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
//     //     }
//     // };

//     // /* GET /latestchain gets latest blockchain and sends it*/
//     // server.resource["^/latestchain$"]["GET"] = [&bc](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
//     //     printf("GET /latestchain --- Sending BlockChain....\n");
//     //     response->write(bc.toJSON());
//     //     printf("---Sent current BlockChain\n");
//     // };

//     // /* POST /newchain called by a node when a new block is added to it -
//     //  * checks whether the length of the blockchain is bigger than our own blockchain
//     //  * if it is bigger -> replace chain, else don't do anything
//     // */
//     // server.resource["^/newchain$"]["POST"] = [&bc](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
//     //     std::cout << "POST /newchain --- Node in Network sent new chain\n";
//     //     try {
//     //         json content = json::parse(request->content);
//     //         if (content["length"].get<int>() > bc.getNumOfBlocks()){
//     //             bc.replaceChain(content);
//     //             cout << "----Replaced current chain with new one" << endl;
//     //             response->write("Replaced Chain\n");
//     //         }
//     //         else {Error:
//     //             std::cout << "----Chain was not replaced: sent chain had same size" <<endl;
//     //             response->write("Same Chain Size -- invalid");
//     //         }
//     //     }
//     //     catch(const exception &e) {
//     //         *response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
//     //     }
//     // };

//     // // On error lambda function
//     // server.on_error = [](shared_ptr<HttpServer::Request> /*request*/, const SimpleWeb::error_code & ec) {
//     //     if (ec.message() != "End of file") {
//     //         std:cout << "SERVER ERROR: " << ec.message() << std::endl;
//     //     }
//     //   };
//     // printf("Starting server at %d",server.config.port);

//     // // start server
//     // std::thread server_thread([&server]() {
//     //     server.start();
//     // });

//     // //COMMAND LINE INTERFACE

//     // // loop for 20 inputs - can change
//     // for(ptrdiff_t i {0}; i < 20; ++i) {

//     //     std::vector<std::string> v{};
//     //     int temp{};

//     //     // ask for what to do
//     //     printf("\n(1) Look at Blocks \n(2) Add block\n");
//     //     int valid = scanf("%d",&temp);

//     //     if ( (valid == 1) && (temp == 1)){ // queue up block if 1
//     //         printf("What Block do you want to look at? ");
//     //         scanf("%d",&temp);
//     //         try {
//     //             bc.getBlock(temp).toString();
//     //         }
//     //         catch (const exception& e){
//     //             std::cout << e.what() << std::endl;
//     //         }
//     //     }
//     //     else if (temp == 2){ // add a new block if 2
//     //         char tmp[201];
//     //         printf("\nADDING BLOCKS!\nEnter your message: ");
//     //         scanf("%200s",tmp);
//     //         std::string str = tmp;
//     //         printf("Entered '%s' into block\n",str.c_str());
//     //         v.push_back(str);

//     //         int in;
//     //         printf("Press any number to add block to blockchain: ");
//     //         scanf("%d",&in);

//     //         try {
//     //             if (bc.getNumOfBlocks() == 0) {
//     //                 printf("----------------------------------\nPlease join the network... Your blockchain doesn't have any blocks ");
//     //                 continue;
//     //             }

//     //             // mine for the hash
//     //             auto pair = findHash(bc.getNumOfBlocks(),bc.getLastBlockHash(),v);
//     //             // add the block to the blockchain
//     //             bc.addBlock(bc.getNumOfBlocks(),bc.getLastBlockHash(),pair.first,pair.second,v );
//     //             // send the blockchain to the network
//     //             sendNewChain(&listOfNodes,bc.toJSON());
//     //         }
//     //         catch (const exception& e) {
//     //             std::cout << e.what() << "\n" << endl;
//     //         }
//     //     }
//     // }

//     // // bc.addBlock(0,string("00000000000000"),string("003d9dc40cad6b414d45555e4b83045cfde74bcee6b09fb42536ca2500087fd9"),string("46"),v);
//     // printf("\n");
//     // return 0;

// }


// Dear ImGui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui.h>
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int, char**)
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}