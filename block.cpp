#include <QDebug>
#include <QFontMetrics>


#include "mainwindow.h"
#include "block.h"


Block::Block(const unsigned long long id, QWidget* parent)
:
QWidget(parent),
mID(id)
{
	// initialize the widget
	this->setStyleSheet(((MainWindow*)this->parent())->getBlockCss());

	// initialize the block
	mBackground = new QLabel(this);
	mLayout = new QGridLayout(this);
	mTitle = new QLabel(this);
	mAddIn = new QPushButton("Add Input", this);
	mAddOut = new QPushButton("Add Output", this);
	mPopIn = new QPushButton("Pop Input", this);
	mPopOut = new QPushButton("Pop Output", this);
	mTitle->setAlignment(Qt::AlignCenter);
	mTitle->setMargin(8);
	mTitle->setObjectName("BlockTitle");
	mBackground->setObjectName("BlockBackground");

	// initialize the layout
	mLayout->setMargin(0);
	mLayout->setSpacing(0);

	// set size
	mLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
	mBackground->setFixedSize(this->size());

	// set default title
	updateText("asdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdf");
	QFont font = mTitle->font();
	font.setPointSize(font.pointSize() + 10);
	mTitle->setFont(font);

	// add stuff to widget
	mLayout->addWidget(mTitle, 0, 0, 1, 3, Qt::AlignCenter);
	mLayout->addWidget(mAddIn, 1, 0);
	mLayout->addWidget(mAddOut, 1, 2);
	mLayout->addWidget(mPopIn, 2, 0);
	mLayout->addWidget(mPopOut, 2, 2);

	// setup buttons
	connect(mAddIn, SIGNAL(clicked(bool)), this, SLOT(addInput()));
	connect(mAddOut, SIGNAL(clicked(bool)), this, SLOT(addOutput()));
	connect(mPopIn, SIGNAL(clicked(bool)), this, SLOT(popInput()));
	connect(mPopOut, SIGNAL(clicked(bool)), this, SLOT(popOutput()));

	mBackground->show();
	this->setLayout(mLayout);
}


Block::~Block()
{
}


void
Block::updateText(const QString &str)
{
	mTitleText = str;
	for (int i = mTitleText.length(); i < 64; i += 2)
	{
		mTitleText.insert(0, ' ');
		mTitleText.insert(mTitleText.length(), ' ');
	}
	mTitle->setText(mTitleText);
	this->adjustSize();
}


void
Block::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		mDragPos = event->globalPos() - frameGeometry().topLeft();
		event->accept();
	}
	else if (event->button() == Qt::RightButton)
	{
		this->close();
		event->accept();
		((MainWindow*)this->parent())->deleteBlock(mID);
	}
	else if (event->button() == Qt::MiddleButton)
	{
		//mTitleText = "asdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdf";
		updateText("a");
	}
}


void
Block::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		this->move(event->globalPos() - mDragPos);
		event->accept();
	}
}


void
Block::wheelEvent(QWheelEvent* event)
{
	QFont font = mTitle->font();
	font.setPointSize(font.pointSize() + ((event->delta() / 120) * 8));
	mTitle->setFont(font);
	font.setPointSize(font.pointSize() - 10);
	if (font.pointSize() < 30)
	{
		font.setPointSize(30);
	}
	mAddIn->setFont(font);
	mAddOut->setFont(font);
	mPopIn->setFont(font);
	mPopOut->setFont(font);
	for (auto& i : mInput)
	{
		i->setFont(font);
	}
	for (auto& i : mOutput)
	{
		i->setFont(font);
	}
	this->adjustSize();
}


void
Block::resizeEvent(QResizeEvent*)
{
	mBackground->setFixedSize(this->size());
}


void
Block::addInput()
{
	QLabel *label = new QLabel("Input", this);
	label->setObjectName("BlockInput");
	label->setAlignment(Qt::AlignCenter);
	label->setMargin(8);
	mInput.push_back(label);
	mLayout->addWidget(label, mInput.size() + 2, 0);
}


void
Block::addOutput()
{
	QLabel *label = new QLabel("Output", this);
	label->setObjectName("BlockOutput");
	label->setAlignment(Qt::AlignCenter);
	label->setMargin(8);
	mOutput.push_back(label);
	mLayout->addWidget(label, mOutput.size() + 2, 2);
}


void
Block::popInput()
{
	if (!mInput.size()) return;
	delete mInput[mInput.size() - 1];
	mInput.pop_back();
	this->adjustSize();
}


void
Block::popOutput()
{
	if (!mOutput.size()) return;
	delete mOutput[mOutput.size() - 1];
	mOutput.pop_back();
	this->adjustSize();
}





