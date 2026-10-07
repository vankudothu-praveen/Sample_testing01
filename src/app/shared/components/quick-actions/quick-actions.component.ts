import {
  ChangeDetectionStrategy,
  Component,
  Input,
} from '@angular/core';

import { NgFor } from '@angular/common';
import { ActionCardComponent } from '../action-card/action-card.component';

@Component({
  selector: 'app-quick-actions',
  standalone: true,
  imports: [NgFor, ActionCardComponent],
  templateUrl: './quick-actions.component.html',
  styleUrl: './quick-actions.component.scss',
  changeDetection: ChangeDetectionStrategy.OnPush,
})
export class QuickActionsComponent {
  @Input() actions: any[] = [];

  trackByLabel(_: number, item: any) {
    return item.label;
  }
}
