import {
  ChangeDetectionStrategy,
  Component,
  Input,
} from '@angular/core';

import { CurrencyPipe } from '@angular/common';

@Component({
  selector: 'app-transaction-item',
  standalone: true,
  imports: [CurrencyPipe],
  templateUrl: './transaction-item.component.html',
  styleUrl: './transaction-item.component.scss',
  changeDetection: ChangeDetectionStrategy.OnPush,
})
export class TransactionItemComponent {
  @Input() transaction: any;
}
