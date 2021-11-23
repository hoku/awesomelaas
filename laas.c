#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

// リップの構成要素1
char msg1[13][60] = {
    {"いやほんと"},
    {"ていうか"},
    {"ほんとに"},
    {"なんていうか"},
    {"マジで"},
    {"すごい"},
    {"すごく"},
    {"超"},
    {"普通に"},
    {"かなり"},
    {"なんか"},
    {"とっても"},
    {"とても"}};

// リップの構成要素2
char msg2[56][60] = {
    {"格好いい"},
    {"イケてる"},
    {"優しい"},
    {"かわいい"},
    {"すごい"},
    {"頼りになる"},
    {"信頼できる"},
    {"堂々としてる"},
    {"礼儀正しい"},
    {"意識が高い"},
    {"忍耐力がある"},
    {"勘が鋭い"},
    {"頑張ってる"},
    {"思いやりがある"},
    {"責任感がある"},
    {"理解力がある"},
    {"輝いてる"},
    {"活き活きとしてる"},
    {"魅力に溢れてる"},
    {"センスがいい"},
    {"パワーがみなぎってる"},
    {"キラキラしてる"},
    {"安心感がある"},
    {"華がある"},
    {"器が大きい"},
    {"心が広い"},
    {"心が澄んでる"},
    {"機転が効く"},
    {"品がある"},
    {"ユーモアがある"},
    {"面白い"},
    {"行動力がある"},
    {"自分を持ってる"},
    {"集中力がある"},
    {"パッションがある"},
    {"芯が強い"},
    {"親近感がある"},
    {"人柄がいい"},
    {"性格がいい"},
    {"存在感がある"},
    {"肝が据わってる"},
    {"柔軟な発想力がある"},
    {"雰囲気がいい"},
    {"勇気がある"},
    {"気が利く"},
    {"頭いい"},
    {"頭の回転が早い"},
    {"物事を冷静に考えられる"},
    {"色んな才能がある"},
    {"いいアドバイスくれる"},
    {"プロ意識がある"},
    {"筋が通ってる"},
    {"包容力がある"},
    {"夢を実現する力がある"},
    {"本質を見抜く力がある"},
    {"才能ある"}};

// リップの構成要素3（「ね」と「よね」の出現率を上げておく）
char msg3[11][30] = {
    {"ね"},
    {"ね"},
    {"ね"},
    {"ね"},
    {"よね"},
    {"よね"},
    {"よね"},
    {"と思うよ"},
    {"と思うよ"},
    {"じゃん"},
    {""}};

// リップの構成要素4（「！」の出現率を上げておく）
char msg4[10][30] = {
    {"！"},
    {"！"},
    {"！"},
    {"！"},
    {"！"},
    {"！"},
    {"！"},
    {"。"},
    {"!!"},
    {"!!!"}};

// 返却するリップ
char result_message[100];
// 返却するhttpレスポンス
char result_http[1000];


int main(void) {
    // 変数
    int sock, client_sock;                // ソケット
    struct sockaddr_in addr, client_addr; // ソケットアドレス
    int addr_length;                      // ソケットアドレスサイズ
    char* return_message;                 // 返却するメッセージ

    // ソケットアドレスサイズを取得しておく
    addr_length = sizeof(client_addr);

    // ソケット作成
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket create");
        return -1;
    }

    // 待受用のソケットアドレス設定
    addr.sin_family      = AF_INET;
    addr.sin_port        = htons(80);
    addr.sin_addr.s_addr = INADDR_ANY;

    // ソケットにバインド
    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("socket bind");
        return -1;
    }

    // リッスン
    if (listen(sock, 10) < 0) {
        perror("socket listen");
        return -1;
    }

    // 乱数を初期化
    srand((unsigned int)time(NULL));

    while (1) {
        // 接続要求を待ち受ける
        client_sock = accept(sock, (struct sockaddr *)&client_addr, &addr_length);

        // 今回のリップを生成
        sprintf(result_message, "{\"lip\":\"%s%s%s%s\"}",
            msg1[rand() % (sizeof(msg1) / sizeof(msg1[0]))],
            msg2[rand() % (sizeof(msg2) / sizeof(msg2[0]))],
            msg3[rand() % (sizeof(msg3) / sizeof(msg3[0]))],
            msg4[rand() % (sizeof(msg4) / sizeof(msg4[0]))]);

        // httpレスポンスを生成
        sprintf(result_http, "%s%s%s%s%d%s%s%s%s%s",
            "HTTP/1.1 200 OK\r\n",
            "Content-Type: application/json; charset=UTF-8\r\n",
            "Server: HokuServer\r\n",
            "Content-Length: ",
            strlen(result_message),
            "\r\n",
            "Connection: close\r\n",
            "Access-Control-Allow-Origin: *\r\n",
            "\r\n",
            result_message);

        // httpレスポンスを出力
        write(client_sock, result_http, strlen(result_http));

        // クローズ
        close(client_sock);
    }

    close(sock);
    return 0;
}
