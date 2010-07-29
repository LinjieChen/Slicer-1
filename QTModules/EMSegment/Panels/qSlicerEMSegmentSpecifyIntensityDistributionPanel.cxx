// Qt includes
#include <QDebug>

// SlicerQt includes
#include "qSlicerEMSegmentSpecifyIntensityDistributionPanel.h" 
#include "ui_qSlicerEMSegmentSpecifyIntensityDistributionPanel.h"

//-----------------------------------------------------------------------------
class qSlicerEMSegmentSpecifyIntensityDistributionPanelPrivate : public ctkPrivate<qSlicerEMSegmentSpecifyIntensityDistributionPanel>,
                                              public Ui_qSlicerEMSegmentSpecifyIntensityDistributionPanel
{
public:
  qSlicerEMSegmentSpecifyIntensityDistributionPanelPrivate()
    {
    }
};

//-----------------------------------------------------------------------------
qSlicerEMSegmentSpecifyIntensityDistributionPanel::qSlicerEMSegmentSpecifyIntensityDistributionPanel(QWidget *_parent):
Superclass(_parent)
{
  CTK_INIT_PRIVATE(qSlicerEMSegmentSpecifyIntensityDistributionPanel);
  CTK_D(qSlicerEMSegmentSpecifyIntensityDistributionPanel);
  d->setupUi(this);
}

//-----------------------------------------------------------------------------
void qSlicerEMSegmentSpecifyIntensityDistributionPanel::printAdditionalInfo()
{
}