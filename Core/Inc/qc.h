#ifndef __QC_H__
#define __QC_H__

#define QC_HANDSHAKE_DELAY_MS (1500)
#define QC_V_CHANGE_DELAY_MS (60)

void QC_Init();
void QC_Handshake();
void QC_Set5V();
void QC_Set9V();
void QC_Set12V();

#endif
