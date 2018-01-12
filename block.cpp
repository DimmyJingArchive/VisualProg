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
	mBackground->setObjectName("BlockBackground");
	mTitle = new QLabel(this);
	mTitle->setAlignment(Qt::AlignCenter);
	mTitle->setObjectName("BlockTitle");
	mAddIn = new QPushButton("Add Input", this);
	mAddOut = new QPushButton("Add Output", this);
	mPopIn = new QPushButton("Pop Input", this);
	mPopOut = new QPushButton("Pop Output", this);

	// initialize the layout
	mLayout = new QGridLayout(this);
	mLayout->setMargin(0);
	mLayout->setSpacing(0);
	mLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

	// set default title
	updateText("Code Block");
	adjustLabelSize();

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

	// show the widgets
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
	// add white spaces before and after the text
	for (int i = mTitleText.length(); i < eTitleMinSize; i += 2)
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
	if (event->buttons() & Qt::LeftButton)
	{
		mDragPos = event->globalPos() - frameGeometry().topLeft();
		event->accept();
	}
	else if (event->buttons() & Qt::RightButton)
	{
		this->close();
		((MainWindow*)this->parent())->deleteBlock(mID);
		event->accept();
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
	QFont font = this->font();
	font.setPointSize(font.pointSize() + ((event->delta() / 120) * 8));
	if (font.pointSize() < eMinFont)
	{
		font.setPointSize(eMinFont);
	}
	this->setFont(font);
	adjustLabelSize();
}


void
Block::resizeEvent(QResizeEvent*)
{
	mBackground->setFixedSize(this->size());
}


void
Block::adjustLabelSize()
{
	QFont font = this->font();
	font.setPointSize(font.pointSize() + eTitleFont);
	mTitle->setFont(font);
	mAddIn->setFont(this->font());
	mPopIn->setFont(this->font());
	mAddOut->setFont(this->font());
	mPopOut->setFont(this->font());
	for (auto& i : mInput) i->setFont(this->font());
	for (auto& i : mOutput) i->setFont(this->font());
	this->adjustSize();
}


void
Block::addInput()
{
	QLabel *label = new QLabel("Input", this);
	label->setObjectName("BlockInput");
	label->setAlignment(Qt::AlignCenter);
	mInput.push_back(label);
	mLayout->addWidget(label, mInput.size() + 2, 0);
	adjustLabelSize();
}


void
Block::addOutput()
{
	QLabel *label = new QLabel("Output", this);
	label->setObjectName("BlockOutput");
	label->setAlignment(Qt::AlignCenter);
	mOutput.push_back(label);
	mLayout->addWidget(label, mOutput.size() + 2, 2);
	adjustLabelSize();
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





