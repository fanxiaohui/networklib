
/*******************************************
*文件名:Message.c
*一个简单的信息提示框
*编译命令： gcc source.c  `pkg-config --cflags --libs gtk+-2.0`
******************************************/
//包含 GTK+的头文件
#include<gtk/gtk.h>

//支持多语言
char const  *_(char const *c)
{
    return(g_locale_to_utf8(c,-1,0,0,0));
}


//标准的 main()函数入口
int main( int argc, char *argv[])
{
	GtkWidget *dialog;
	gtk_init(&argc, &argv);
	//声明一个对话框
	//初始化 GTK
	//使用 gtk_message_dialog_new()函数新建一个消息对话框
	dialog = gtk_message_dialog_new(NULL,
	    GTK_DIALOG_DESTROY_WITH_PARENT,
    	GTK_MESSAGE_WARNING,
	    GTK_BUTTONS_OK,
        _("牛奶会有的......\n 面包会有的......")
    );

//没有父窗口
	//跟随父窗口关闭
	//显示警告图标
	//显示 OK 按钮
	//提示信息的内容
	gtk_window_set_title(
        GTK_WINDOW(dialog), 
        _("牛奶与面包")
    ); //对话框的标题栏
	
    gtk_dialog_run(GTK_DIALOG(dialog));
	//运行对话框
	gtk_widget_destroy(dialog);
	//删除对话框
	gtk_main();//主函数循环,等待消息
	return 0;
}//==============main 函数结束===========================


