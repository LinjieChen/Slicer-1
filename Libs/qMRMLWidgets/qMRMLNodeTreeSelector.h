#ifndef __qMRMLNodeTreeSelector_h
#define __qMRMLNodeTreeSelector_h

// qMRML includes
#include "qMRMLNodeSelector.h"

// qCTK includes
#include <qCTKPimpl.h>

#include "qMRMLWidgetsWin32Header.h"

class qMRMLNodeTreeSelectorPrivate;

class QMRML_WIDGETS_EXPORT qMRMLNodeTreeSelector : public qMRMLNodeSelector
{
  Q_OBJECT
public:
  // Superclass typedef
  typedef qMRMLNodeSelector Superclass;
  
  // Constructors
  qMRMLNodeTreeSelector(QWidget* parent = 0);

protected:
  virtual void addNodeInternal(vtkMRMLNode* mrmlNode);
  
private:
  QCTK_DECLARE_PRIVATE(qMRMLNodeTreeSelector);
};

#endif
