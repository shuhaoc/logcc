#pragma once

struct LogItem;

/**
 * ��־��ѯ��ÿ�������Ӧһ����־�ļ�
 * @author CaoShuhao
 * @date 2014-1-12
 */
class ILogQuery {
public:
	virtual ~ILogQuery() { }

	/**
	 * ͬ����ȡ�ļ���������
	 * @param filePath [in] �ļ���
	 * @author CaoShuhao
	 * @date 2014-1-12
	 */
	virtual bool load(const tstring& filePath) = 0;

	/**
	 * ��ȡ��־·��
	 * @return 
	 * @author CaoShuhao
	 * @date 2014-1-12
	 */
	virtual const tstring& getFilePath() const = 0;

	/**
	 * ��ѯ����
	 * @author CaoShuhao
	 * @date 2014-1-12
	 */
	virtual unsigned getLineCount() const = 0;

	/**
	 * ��ȡ������[begin, end)�����ڵ���־��
	 * @param begin [in] ��ʼ��
	 * @param end [in] ���һ�е���һ��
	 * @author CaoShuhao
	 * @date 2014-1-12
	 */
	virtual vector<LogItem*> getRange(unsigned begin, unsigned end) const = 0;
};