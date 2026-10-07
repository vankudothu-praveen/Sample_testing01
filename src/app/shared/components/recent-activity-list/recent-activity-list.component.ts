import {
  ChangeDetectionStrategy,
  Component,
  Input,
} from '@angular/core';

import { NgFor } from '@angular/common';
import { TransactionItemComponent } from '../transaction-item/transaction-item.component';

@Component({
  selector: 'app-recent-activity-list',
  standalone: true,
  imports: [NgFor, TransactionItemComponent],
  templateUrl: './recent-activity-list.component.html',
  styleUrl: './recent-activity-list.component.scss',
  changeDetection: ChangeDetectionStrategy.OnPush,
})
export class RecentActivityListComponent {
  @Input() transactions: any[] = [];

  trackById(_: number, item: any) {
    return item.id;
  }
}
