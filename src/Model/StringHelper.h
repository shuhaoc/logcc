#pragma once

#include <string>
#include <vector>
#include "Common.h"

namespace common
{
	namespace utility
	{
		/*
		* �����ַ���������һЩ��װ��ȫ����д��ȫ��Сд�����ַ�תansi��ansiת���ַ��ȡ�
		*/
		namespace stringhelper
		{
			/*
			/*ansi��ʹ�ַ���ȫ��Сд
			* @param [in] in_str �����ַ���
			* @return ����ֵ�������ַ�����Сдֱ�ӷ���
			*/
			COMMON_INTERFACE std::string MakeLowerA(std::string& in_str);

			/*
			/*ansiʹ�ַ���ȫ��Сд
			* @param [in] in_str �����ַ��������봮�����
			* @return ����ֵ�������ַ�����Сд���´��������´�
			*/
			COMMON_INTERFACE std::string MakeLowerCopyA(const std::string& in_str);

			/*
			/*���ַ���ʹ�ַ���ȫ��Сд
			* @param [in] in_str �����ַ���
			* @return ����ֵ�������ַ�����Сдֱ�ӷ���
			*/
			COMMON_INTERFACE std::wstring MakeLower(std::wstring& in_str);

			/*
			/*���ַ���ʹ�ַ���ȫ��Сд
			* @param [in] in_str �����ַ��������봮�����
			* @return ����ֵ�������ַ�����Сд���´��������´�
			*/
			COMMON_INTERFACE std::wstring MakeLowerCopy(const std::wstring& in_str);

			/*
			/*ansi��ʹ�ַ���ȫ����д
			* @param [in] in_str �����ַ���
			* @return ����ֵ�������ַ������дֱ�ӷ���
			*/
			COMMON_INTERFACE std::string MakeUpperA(std::string& in_str);

			/*
			/*ansi��ʹ�ַ���ȫ����д
			* @param [in] in_str �����ַ��������봮�����
			* @return ����ֵ�������ַ������д���´��������´�
			*/
			COMMON_INTERFACE std::string MakeUpperCopyA(const std::string& in_str);

			/*
			/*���ַ���ʹ�ַ���ȫ����д
			* @param [in] in_str �����ַ���
			* @return ����ֵ�������ַ������д���´��������´�
			*/
			COMMON_INTERFACE std::wstring MakeUpper(std::wstring& in_str);

			/*
			/*����ֵ�������ַ�����Сд���´��������´�
			* @param [in] in_str �����ַ��������봮�����
			* @return ����ֵ�������ַ������дֱ�ӷ���
			*/
			COMMON_INTERFACE std::wstring MakeUpperCopy(const std::wstring& in_str);

			/*
			* ���ַ���תΪ����
			* @param [in] in_str �����Դ�ַ��������ݲ��޸�
			* @param [out] iRetInt ���ص�����ֵ������ֵ��ȷʱ������֮
			* @return ����true��ʾ�ɹ���falseʧ�ܣ�ʧ��ԭ���ַ���Ϊ�յ� 
			*/
			COMMON_INTERFACE bool StringToIntA(const std::string& in_str, int* iRetInt);

			/*
			* ���ַ���תΪ����
			* @param [in] in_str �����Դ�ַ��������ݲ��޸�
			* @return ת��ʧ�ܷ���Ϊ0 
			*/
			COMMON_INTERFACE int StringToIntA(const std::string& in_str);

			/*
			* �ӿ��ַ���תΪ����
			* @param [in] in_str �����Դ���ַ��������ݲ��޸�
			* @param [out] bRetInt ���ص�����ֵ������ֵ��ȷʱ������֮
			* @return ����true��ʾ�ɹ���falseʧ�ܣ�ʧ��ԭ���ַ���Ϊ�յ� 
			*/
			COMMON_INTERFACE bool StringToInt(const std::wstring& in_str, int* bRetInt);

			/*
			* ���ַ���תΪ����
			* @param [in] in_str �����Դ�ַ��������ݲ��޸�
			* @return ת��ʧ�ܷ���Ϊ0 
			*/
			COMMON_INTERFACE int StringToInt(const std::wstring& in_str);

			/*
			* ���ַ���תΪ����
			* @param [in] inNUM ���������ֵ������Ϊ���������һ�����ţ�
			* @return ����ΪNULLʱ��ת��ʧ��
			*/
			COMMON_INTERFACE std::string IntToStringA(int inNUM);

			/*
			* �ӿ��ַ���תΪ����
			* @param [in] inNUM ���������ֵ������Ϊ���������һ�����ţ�
			* @return ����ΪNULLʱ��ת��ʧ��
			*/
			COMMON_INTERFACE std::wstring IntToString(int inNUM);

			/*
			* �ӿ��ַ���תΪ����
			* @param [in] inNUM ���������ֵ������Ϊ���������һ�����ţ�
			* @return ����ΪNULLʱ��ת��ʧ��
			*/
			COMMON_INTERFACE std::wstring Int64ToString(__int64 inNUM);

			/*
			* �ӿ��ַ���תΪansi�ַ���
			* @param [in] in_str Ϊ�����Դansi�ַ�
			* @return ����ֵΪ���ַ���
			*/
			COMMON_INTERFACE std::string UnicodeToAscii(const std::wstring& in_str);

			/*
			* ��ansi�ַ���תΪ���ַ���
			* @param [in]  in_str Ϊ�����Դansi�ַ�
			* @return ����ֵΪansi�ַ���
			*/
			COMMON_INTERFACE std::wstring AsciiToUnicode(const std::string& in_str);

			/*
			* ��utf8�ַ���תΪ���ַ���
			* @param [in] in_utf8Str ����UTF8�ַ���
			* @return ����ֵΪUNICODE�ַ��������ת��ʧ�ܣ�����NULL
			*/
			COMMON_INTERFACE std::wstring UTF8ToUnicode(const std::string& in_utf8Str);

			/*
			* �ӿ��ַ���תΪutf8�ַ���
			* @param [in] in_wStr ������ַ���
			* @return ����ֵΪUTF8�ַ��������ת��ʧ�ܣ�����NULL
			*/		
			COMMON_INTERFACE std::string UnicodeToUTF8(const std::wstring& in_wStr);

			/*
			* ansi�汾���ж��ַ����Ƿ�ȫ���������
			* @param [in] in_str ������ַ���
			* @return ����ֵΪtrueʱ���������ȫ��������ɵ��ַ��������򷵻�false
			*/	
			COMMON_INTERFACE bool IsNumeric(const std::string& in_str);

			/*
			* UNICODE�汾���ж��ַ����Ƿ�ȫ���������
			* @param [in] in_str ������ַ���
			* @return ����ֵΪtrueʱ���������ȫ��������ɵ��ַ��������򷵻�false
			*/	
			COMMON_INTERFACE bool IsNumeric(const std::wstring& in_str);


			/*
			* UNICODE�汾���ж��ַ��Ƿ�����ascii�ַ���ͳ��Ϊһ���ַ�
			* @param [in] in_chr ����Ŀ��ַ�
			* @return ����ֵΪtrueʱ�����������ascii�ַ������򷵻�false
			*/	
			COMMON_INTERFACE bool IsCharAscii(const wchar_t in_chr);

			/*
			* UNICODE�汾��ͳ���ַ����������ַ�����Ϊ2��anscii����Ϊ1
			* @param [in] in_str ����Ŀ��ַ���
			* @return ����ֵΪansi�����������ascii�ַ������򷵻�false
			*/
			COMMON_INTERFACE size_t CalcStringAsciiLength(const wchar_t* in_str);	

			/*
			* UNICODE�汾��ͳ���ַ����������ַ�����Ϊ2��anscii����Ϊ1
			* @param [in] in_str ����Ŀ��ַ���
			* @return ����ֵΪansi�����������ascii�ַ������򷵻�false
			*/
			COMMON_INTERFACE size_t CalcStringAsciiLength(const std::wstring& in_str);	

			/*
			* ��ȡ�ַ�����ָ����Ŀ��anscii����ִ�
			* @param [in] in_str ����Ŀ��ַ���
			* @param [in][out] szRet ���ص����ַ���
			* @param [in] nMaxInByte ��������ַ���������ַ���Ŀ�����ַ�����Ϊ2��anscii����Ϊ1��
			* @return ����ֵΪ���ַ����а�����anscii����Ŀ
			*/
			COMMON_INTERFACE size_t GetSubstrInAnsi(const std::wstring& in_str, std::wstring& szRet, size_t nMaxInByte);

			/*
			* ���ַ�������β�հ��ַ��Ƴ��������ո�' ' ����\n �س�\r �Ʊ��\�ȣ�����
			* @param [in] in_str �����ַ���
			* @return ����ֵΪɾ���հ״����ַ�����ֱ�Ӷ����봮����
			*/	
			COMMON_INTERFACE std::string TrimA(std::string& in_str);

			/*
			* ���ַ�������β�հ��ַ��Ƴ�
			* @param [in] in_Str �����ַ���
			* @return ����ֵΪɾ���հ״������ַ���
			*/	
			COMMON_INTERFACE std::string TrimCopyA(const std::string& in_str);

			/*
			* �����ַ�������β�հ��ַ��Ƴ�
			* @param [in] in_wStr ������ַ���
			* @return ����ֵΪɾ���հ״��Ŀ��ַ�����ֱ�Ӷ����봮����
			*/	
			COMMON_INTERFACE std::wstring Trim(std::wstring& in_wStr);

			/*
			* �����ַ�������β�հ��ַ��Ƴ�
			* @param [in] in_wStr ������ַ���
			* @return ����ֵΪɾ���հ״����¿��ַ���
			*/	
			COMMON_INTERFACE std::wstring TrimCopy(const std::wstring& in_str);

			/*
			* ���ַ����и��ݽض��ַ����нضϣ�ע�⣺ɾ������β�Ŀհ��ַ���
			* @param [in] in_str �����ַ���
			* @param [in] cSplit ����Ľض��ַ�
			* @return ����ֵ�ضϵĸ����ִ�������ַ�����û�нض��ַ��Ļ���vector��СΪ0
			*/	
			COMMON_INTERFACE std::vector<std::string> Split_String_by_DelimiterA(const std::string& in_str, char cSplit);

			/*
			* �ӿ��ַ����и��ݽض��ַ����нضϣ�ע�⣺ɾ������β�Ŀհ��ַ���
			* @param [in] in_wStr ������ַ���
			* @param [in] cSplit ����ĽضϿ��ַ�
			* @return ����ֵ�ضϵĸ����ӿ��ַ���������ַ�����û�нض��ַ��Ļ���vector��СΪ0
			*/	
			COMMON_INTERFACE std::vector<std::wstring> Split_String_by_Delimiter(const std::wstring& in_wStr, wchar_t cSplit);

			/*
			* format�ַ���
			* @param [in] format ��ʽ���ַ���
			* @return ����Ϊ��ʽ���ַ����������ʽ����ʽʱ�������NULL
			*/
			COMMON_INTERFACE std::string FormatA(const char* format, ...);

			/*
			* �ӿ��ַ���תΪutf8�ַ���
			* @param [in] format ���ַ��ĸ�ʽ���ַ���
			* @return ����Ϊ��ʽ���ַ����������ʽ����ʽʱ�������NULL
			*/
			COMMON_INTERFACE std::wstring Format(const wchar_t* format, ...);

			/*��ascii���ִ�ת��Ϊhex�ִ���ͨ������url�Ĳ����������get_token_string��AsciiToHex������
			* �ӿ��ַ���תΪutf8�ַ���
			* @param [in] token �����ַ���
			* @return ����ΪHex���ַ���
			*/
			COMMON_INTERFACE std::string HexEncodeCopy(const std::string& in_str);

			/*��ascii���ִ�ת��Ϊhex�ִ���ͨ������url�Ĳ����������get_token_string��AsciiToHex������
			* �ӿ��ַ���תΪutf8�ַ���
			* @param [in] in_str �����ַ���ָ��
			* @param [in] size �����ַ���ָ����ָ���ִ�����
			* @return ����ΪHex���ַ����������������ʱ������ΪNULL
			*/
			COMMON_INTERFACE std::string HexEncodeCopy(const char* in_str, size_t size);

			/*
			/*XML�ı��ж�Ӧ��ascii���ַ�������
			* @param [in] in_xmlStr ����ѹ��ǰ���ַ���
			* @return ����Ϊѹ������ַ����������´�
			*/
			COMMON_INTERFACE std::string XMLEncodeA(const std::string& in_xmlStr);

			/*
			/*XML�ı��ж�Ӧ��unicode���ַ�������
			* @param [in] in_xmlStr ����ѹ��ǰ���ַ���
			* @return ����Ϊѹ������ַ����������´�
			*/
			COMMON_INTERFACE std::wstring XMLEncode(const std::wstring& in_xmlStr);

			/*
			/*XML�ı��ж�Ӧ��ascii���ַ�������
			* �ӿ��ַ���תΪutf8�ַ���
			* @param [in] in_xmlStr ����ѹ�����ַ���
			* @return ����Ϊ��ѹ������ַ����������´�
			*/
			COMMON_INTERFACE std::string XMLDecodeA(const std::string& in_xmlStr);

			/*
			/*XML�ı��ж�Ӧ��unicode���ַ�������
			* @param [in] in_xmlStr ����ѹ�����ַ���
			* @return ����Ϊ��ѹ������ַ����������´�
			*/
			COMMON_INTERFACE std::wstring XMLDecode(const std::wstring& in_xmlStr);

			/** ��std::wstring����Replace����
			* @param [in][out] std::wstring &str,���滻���ַ���
			* @param [in] const std::wstring &strSrc,Ҫ���滻��Դ�ַ��Ӵ�
			* @param [in] const std::wstring &strDst,Ҫ���滻��Ŀ���ַ��Ӵ�
			* @return void.
			*/
			COMMON_INTERFACE void Replace(std::wstring &str, const std::wstring &strSrc, const std::wstring &strDst);

			//�ַ�����ö�ٶ���
			enum E_CHARACTER_SET
			{
				SIMPLE_CHINESE       = 0X01,
				TRADITIONAL_CHINESE  = 0X02,
				CHINESE              = SIMPLE_CHINESE | TRADITIONAL_CHINESE,
				ENGLISH              = 0X04,
				KOREA                = 0X08,
				JAPANESE             = 0X10,
				SPANISH              = 0x20,
				FRANCE               = 0x40,
				GERMAN               = 0x80,
				RUSIA                = 0x100,
			};

			/** �ж��ַ������ַ�������
			* @param [in] set, �ַ�����ö��ֵ�����Զ����ϣ��á�|��������
			* @param [in] charcter, ���жϵ��ַ�
			* @return ����Ϊtrueʱ����ʾ�ַ���ָ�����ַ���
			*/
			COMMON_INTERFACE bool IsInCharacterSet(uint32 const &set ,wchar_t const charcter);

			/** �ж��ַ������ַ���������
			* @param [in] set, �ַ�����ö��ֵ�����Զ����ϣ��á�|��������
			* @param [in] charcters, ���жϵ��ַ���
			* @return ����Ϊtrueʱ����ʾ�ַ�������ָ�����ַ���
			*/
			COMMON_INTERFACE bool IsInCharacterSet(uint32 const &set ,std::wstring const charcters);
        };
	};	
};