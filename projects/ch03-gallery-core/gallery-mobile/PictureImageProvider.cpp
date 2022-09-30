#include "PictureImageProvider.h"

#include "PictureModel.h"

const QString PICTURE_SIZE_FULL = "full";
const QString PICTURE_SIZE_THUMBNAIL = "thumbnail";
const QSize PictureImageProvider::THUMBNAIL_SIZE = QSize(350, 350);

PictureImageProvider::PictureImageProvider(PictureModel* pictureModel)
  : QQuickImageProvider(QQuickImageProvider::Pixmap)
  , mPictureModel(pictureModel)
{
}

/*
 * images://pictures/<index>/full: this syntax is used to retrieve
the full resolution image.
• images://pictures/<index>/thumbnail: this syntax is used to
retrieve the thumbnail version of the image.
 */
QPixmap
PictureImageProvider::requestPixmap(const QString& id,
                                    QSize* /*size*/,
                                    const QSize& /*requestedSize*/)
{
  QStringList query = id.split('/');
  if (!mPictureModel || query.size() < 2) {
    return QPixmap();
  }

  int row = query[0].toInt();
  QString pictureSize = query[1];
  QUrl fileUrl =
    mPictureModel
      ->data(mPictureModel->index(row, 0), PictureModel::Roles::UrlRole)
      .toUrl();

  // use our own cache function
  return *pictureFromCache(fileUrl.toLocalFile(), pictureSize);
}

QPixmap*
PictureImageProvider::pictureFromCache(const QString& filepath,
                                       const QString& pictureSize)
{
  QString key = pictureSize + "-" + filepath;

  // add picture to cache if it isn't cached
  if (!mPicturesCache.contains(key)) {
    QPixmap* cachePicture = nullptr;
    QPixmap originalPicture(filepath);

    if (pictureSize == PICTURE_SIZE_THUMBNAIL) {
      cachePicture = new QPixmap(originalPicture.scaled(
        THUMBNAIL_SIZE, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else if (pictureSize == PICTURE_SIZE_FULL) {
      cachePicture = new QPixmap(originalPicture);
    }

    mPicturesCache.insert(key, cachePicture);
    return cachePicture;
  }

  return mPicturesCache[key];
}
