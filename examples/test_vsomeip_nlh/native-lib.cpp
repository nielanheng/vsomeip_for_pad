// #include <jni.h>
// #include <string>
// #include <thread>
// #include <unistd.h>
// #include "Server.h"
// #include "Client.h"

// Server* server;
// Client* client;
// static int val = 1;

// extern "C" JNIEXPORT void JNICALL
// Java_com_beantechs_nativetest_MainActivity_startServer(JNIEnv*,jobject /* this */) {
//     if(!server){
//         server = new Server();
//         server->ready();
//         server->start();
//     }
// }

// extern "C" JNIEXPORT void JNICALL
// Java_com_beantechs_nativetest_MainActivity_startClient(JNIEnv*,jobject /* this */) {
//     if(!client) {
//         client = new Client();
//         client->ready();
//         client->start();
//     }
// }

// extern "C" JNIEXPORT void JNICALL
// Java_com_beantechs_nativetest_MainActivity_setField(JNIEnv*,jobject /* this */) {
//     if(client) {
//         client->callSetField(val);
//         val ++;
//     }
// }

// extern "C" JNIEXPORT void JNICALL
// Java_com_beantechs_nativetest_MainActivity_getField(JNIEnv*,jobject /* this */) {
//     if(client) {
//         client->callGetField();
//     }
// }

// extern "C" JNIEXPORT void JNICALL
// Java_com_beantechs_nativetest_MainActivity_callMethod(JNIEnv*,jobject /* this */) {
//     if(client) {
//         client->callMethod(99);
//     }
// }
