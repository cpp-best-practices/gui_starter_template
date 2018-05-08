#include <QWidget>

class HelloQt : public QWidget
{
	Q_OBJECT // Very Important, this is all the magic that is needed
	public:
		explicit HelloQt( QWidget* parent = nullptr );
		~HelloQt();
	private slots:
		void writeToDebug( void );

};
