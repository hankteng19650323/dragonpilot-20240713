#pragma once

#include <QVBoxLayout>
#include <memory>

#include "selfdrive/ui/qt/onroad/buttons.h"
#include "selfdrive/ui/qt/widgets/cameraview.h"

#ifdef DP
#include "dp_priv/selfdrive/ui/qt/onroad/annotated_camera.h"
#endif

class AnnotatedCameraWidget : public CameraWidget {
  Q_OBJECT

public:
  explicit AnnotatedCameraWidget(VisionStreamType type, QWidget* parent = 0);
  void updateState(const UIState &s);

private:
  void drawText(QPainter &p, int x, int y, const QString &text, int alpha = 255);

  QVBoxLayout *main_layout;
  ExperimentalButton *experimental_btn;
  QPixmap dm_img;
  float speed;
  QString speedUnit;
  float setSpeed;
  bool is_cruise_set = false;
  bool is_metric = false;
  bool dmActive = false;
  bool hideBottomIcons = false;
  bool rightHandDM = false;
  float dm_fade_state = 1.0;
  bool v_ego_cluster_seen = false;
  int status = STATUS_DISENGAGED;
  std::unique_ptr<PubMaster> pm;

  int skip_frame_count = 0;
  bool wide_cam_requested = false;

  #ifdef DP
  FlightPanel *flight_panel;
  PersonalityButton *personality_btn;
  KnightScanner *knight_scanner;
  RainbowPath *rainbow_path;
  ChevronExt *chevron_ext;
  TeTooIndicator *tt_indicator;
  #endif

protected:
  void paintGL() override;
  void initializeGL() override;
  void showEvent(QShowEvent *event) override;
  void updateFrameMat() override;
  void drawLaneLines(QPainter &painter, const UIState *s);
  void drawLead(QPainter &painter, const cereal::RadarState::LeadData::Reader &lead_data, const QPointF &vd);
  void drawHud(QPainter &p);
  void drawDriverState(QPainter &painter, const UIState *s);
  inline QColor redColor(int alpha = 255) { return QColor(201, 34, 49, alpha); }
  inline QColor whiteColor(int alpha = 255) { return QColor(255, 255, 255, alpha); }
  inline QColor blackColor(int alpha = 255) { return QColor(0, 0, 0, alpha); }

  double prev_draw_t = 0;
  FirstOrderFilter fps_filter;
};
