// Qt includes
#include <QDebug>

// SlicerQt includes
#include "qSlicerEMSegmentDefinePreprocessingPanel.h" 
#include "ui_qSlicerEMSegmentDefinePreprocessingPanel.h"

//-----------------------------------------------------------------------------
class qSlicerEMSegmentDefinePreprocessingPanelPrivate : public ctkPrivate<qSlicerEMSegmentDefinePreprocessingPanel>,
                                              public Ui_qSlicerEMSegmentDefinePreprocessingPanel
{
public:
  qSlicerEMSegmentDefinePreprocessingPanelPrivate()
    {
    }
};

//-----------------------------------------------------------------------------
qSlicerEMSegmentDefinePreprocessingPanel::qSlicerEMSegmentDefinePreprocessingPanel(QWidget *_parent):
Superclass(_parent)
{
  CTK_INIT_PRIVATE(qSlicerEMSegmentDefinePreprocessingPanel);
  CTK_D(qSlicerEMSegmentDefinePreprocessingPanel);
  d->setupUi(this);
}

//-----------------------------------------------------------------------------
void qSlicerEMSegmentDefinePreprocessingPanel::printAdditionalInfo()
{
}