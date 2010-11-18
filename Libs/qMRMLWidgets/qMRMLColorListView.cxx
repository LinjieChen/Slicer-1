/*==============================================================================

  Program: 3D Slicer

  Copyright (c) 2010 Kitware Inc.

  See Doc/copyright/copyright.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Julien Finet, Kitware Inc.
  and was partially funded by NIH grant 3P41RR013218-12S1

==============================================================================*/

// QT includes
#include <QSortFilterProxyModel>

// qMRML includes
#include "qMRMLColorListView.h"
#include "qMRMLColorModel.h"

// MRML includes
#include <vtkMRMLColorNode.h>

//------------------------------------------------------------------------------
class qMRMLColorListViewPrivate
{
  Q_DECLARE_PUBLIC(qMRMLColorListView);
protected:
  qMRMLColorListView* const q_ptr;
public:
  qMRMLColorListViewPrivate(qMRMLColorListView& object);
  void init();
};

//------------------------------------------------------------------------------
qMRMLColorListViewPrivate::qMRMLColorListViewPrivate(qMRMLColorListView& object)
  : q_ptr(&object)
{
}

//------------------------------------------------------------------------------
void qMRMLColorListViewPrivate::init()
{
  Q_Q(qMRMLColorListView);

  qMRMLColorModel* colorModel = new qMRMLColorModel(q);
  QSortFilterProxyModel* sortFilterModel = new QSortFilterProxyModel(q);
  sortFilterModel->setSourceModel(colorModel);
  q->setModel(sortFilterModel);
  
  //q->setWrapping(true);
  //q->setResizeMode(QListView::Adjust);
  //q->setFlow(QListView::TopToBottom);
  //q->setRootIndex(sortFilterModel->mapFromSource(colorModel->mrmlColorNodeIndex()));
}

//------------------------------------------------------------------------------
qMRMLColorListView::qMRMLColorListView(QWidget *_parent)
  : QListView(_parent)
  , d_ptr(new qMRMLColorListViewPrivate(*this))
{
  Q_D(qMRMLColorListView);
  d->init();
}

//------------------------------------------------------------------------------
qMRMLColorListView::~qMRMLColorListView()
{
}

//------------------------------------------------------------------------------
qMRMLColorModel* qMRMLColorListView::colorModel()const
{
  return qobject_cast<qMRMLColorModel*>(this->sortFilterProxyModel()->sourceModel());
}

//------------------------------------------------------------------------------
QSortFilterProxyModel* qMRMLColorListView::sortFilterProxyModel()const
{
  return qobject_cast<QSortFilterProxyModel*>(this->model());
}

//------------------------------------------------------------------------------
void qMRMLColorListView::setMRMLColorNode(vtkMRMLNode* node)
{
  this->setMRMLColorNode(vtkMRMLColorNode::SafeDownCast(node));
}

//------------------------------------------------------------------------------
void qMRMLColorListView::setMRMLColorNode(vtkMRMLColorNode* node)
{
  qMRMLColorModel* mrmlModel = this->colorModel();
  Q_ASSERT(mrmlModel);
  mrmlModel->setMRMLColorNode(node);
}

//------------------------------------------------------------------------------
vtkMRMLColorNode* qMRMLColorListView::mrmlColorNode()const
{
  qMRMLColorModel* mrmlModel = this->colorModel();
  Q_ASSERT(mrmlModel);
  return mrmlModel->mrmlColorNode();
}

//------------------------------------------------------------------------------
void qMRMLColorListView::setShowOnlyNamedColors(bool enable)
{
  if (enable)
    {
    this->sortFilterProxyModel()->setFilterRegExp(QRegExp("^(?!\\(none\\))"));
    }
  else
    {
    this->sortFilterProxyModel()->setFilterRegExp(QRegExp());
    }
}

//------------------------------------------------------------------------------
bool qMRMLColorListView::showOnlyNamedColors()const
{
  return this->sortFilterProxyModel()->filterRegExp().isEmpty();
}