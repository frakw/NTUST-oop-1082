//FormWord-inputmain1.cpp
#include"Form.h"
//�D�ػ���:Ū�Jtxt�ɡA�P�_�C�檺���r��U�Ӧr���Ʀ��S������@�ӶW�Linput�r��U�Ӥl���ƪ��ƶq�A�p�G�S�h�L�X�A�Ϥ����L�X
int main()
{
	Form form1;
	form1.SetInputWord("SWIMMING");//�]�wInput
	form1.ProcessInputWord();//�B�zInput��T
	form1.SetFileName("words.txt");//�]�w�ɮצW��
	form1.Load_CompareWord();//Ū�ɨåB���
	form1.PrintFoundWords();//�L�X�ŦX���r
	return 0;
}